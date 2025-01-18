# Protocol
## Introduction

There is 2 type of connections :
- Tcp
- Udp
Each type of connection has its own protocol.

Before starting, here is some useful notation
1. `[]` indicate a pack of octet, with its title inside
For exemple :
`[id]` means there is a pack of octet dedicated for an id.

If there is no further information, it means it is only 1 and only 1 octet
in the previous exemple it would have means that the id is only composed of 1 octet

2. `/{NB}o` idicate a number of octet. This notation goes inside the `[]`
For exemple :
`[ID/4o]` means there is a pack of octet that compose an ID and this id is composed of 4 octets
In case of number and not ID, the bigger numbers come first.
for exemple : `0x2F 34 2A B3` will be sent as :
nb[0] : 2F
nb[1] : 34
nb[2] : 2A
nb[3] : B3

It is also knows as little indian :3
**NB** sometimes, we can have `?` which means undifined number of octets, this notation is more for the strings.

3. `...` is for "prefix", octet that has been declared as "global"
Exemple :
Global prefix :`[2][ID /4o]`
the code : `...[Speed /4o]`

means that the full package is 9 octets longs :
- the single octet for `[2]` - that has the value 2
- the ID on 4 octets `[ID /4o]`
- the speed on 4 octet `[Speed /4o]`
- the result is : `[2][ID /4o][Speed /4o]`
Because the code has `...` and that there is a global prefix, the complete code will be the concatenation of the prefixe and the rest.
**NB** a prefix can have a prefix

4 `[|]` is for choice
it is to illustrate that there is a limited choice, often with a value and the signification
Exemple :
`[Key code][Pressed = 1 | Released = 2]`
meanse that the package is made of 2 octets, the 1st is a key code, the seconde means "Pressed or Released"
`[K][1]` means that the key "K" is pressed while `[A][2]` meanse that the key "A" is released

---

## TCP

First of all, at the beginning of all TCP request, there is 2 octets dedicated to the length of the request.
Prefix : `[size /2o]`

### Server -> Client

1. OK
If the previous instruction previously made succeed
`...[200]`

2. KO
If the previous instruction previously made did not succeed
`...[201]`

3. Room declaration
This request is here to add a new room waiting for new player
`...[1][new = 1 | deleted = 0][room id /1o][room name /?o]`

4. Set ready
It will declare you ready to play. You need to be in a room to set you ready.
The game will start when all player are ready !
`...[2]`

5. Load a sprite
When the game is starting, the server will send to the client everything they need to play.
`...[3][Id of the sprite /4o][Width /4o][Height /4o][Width text rect /4o][Height text rect /4o][X offset /4o][Y offset /4o][Number of frames /4o][nb milisecond per frame /4o][path to the image /?o]`

6. Load a background
`...[4][Speed][move on X axis = 1 | move on Y axis = 2][resize = 1 | do not = 0][loop = 1 | do not loop][Do not move = 1 | Parallax = 2 | Perpetual movement = 3][Path to image /?o]`

7. Load a music
`...[5][id musique][path to musique /?o]`

8. Load an action
`...[6][id action / 4o][key code / 4o][pressed = 1 | released = 0]`

9. Transfert IpPort where the game will take place :
`...[7][IP /4o][Port/2o][Player Id]`
with :
Ip : `[nb1 /1o][nb2 /1o][nb3 /1o][nb4 /1o]` => nb1.nb2.nb3.nb4
Port : `[nb1/1o][nb2/1o]` translation to string then concatenation, for exemple: 9809, NB1 = 98 et NB2 = 09. Translation to STR : NB1 = "98" NB2 = "09" then concatenation => "9809"

10. Declare an existing game:
It sends you an existing game that you can select where you create a room
`...[8][game name]`

11. Someone entered/exited a room:
`...[9][exited = 0 | entered = 1][Room id][name]`

12. Force register in a room:
It force register you in the room you have clicked on to enter
`...[10][Room Id][Room Name]`


### Client -> Server

1. Define a name
`...[1][Name /?o]`
Server response : OK | KO
this instruction is mandatory, it is a loggin

2. Enter in a Room :
`...[2][Id room /1o]`
Server response : OK | KO

3. Leave the current room
`...[4]`
Server response : OK | KO
this will make you leave the room if you are in one and set you not ready

4. List Games
`...[5]`
Server response : `...[8][game name]`

5. Missing file
`...[6][File path /?o]`
Server response : OK[followed by the file (binary)] | KO
when the server give you all the ressourses, it just gives the path. By default it assumes the client has everything.
However, you can ask him the document and then it will give it to you

6. New Room
`...[7][Room Name /?o][92][Name of the game /?o]`
Server response : OK | KO

7. List rooms
`...[8]`
Server response : `...[1][1][room id /1o][room name /?o]`

8. Delete rooms
`...[9][Id room]`

9. Set ready or unready :
`...[10]`
Server response : OK | KO
the game is launched if All player are set ready
this command will set you ready is you are not and will set you not ready if you are

**NB** Be carefull, some instruction of the server can be sent before a response to a request.
For exemple :
Client --{Create a new Room}--> Server
Client <-{Declare a new Room}-- Server
Client <-{OK to the creation}-- Server
as we can see here, the declaration of a new random room has been sent by the server before the confirmation of the room creation.

## UDP
