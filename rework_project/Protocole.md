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
In case of number and not ID, the smaller number goes to the beginning.
for exemple : `0x2F 34 2A B3` will be sent as :
nb[0] : B3
nb[1] : 2A
nb[2] : 34
nb[3] : 2F

It is also knows as little indian :3
**NB** sometimes, we can have `?` which means undifined number of octets, this notation is more for the strings.

3. `...` is for "prefix", octet that has been declared as "global"
Exemple :
Global prefix :`[2][ID/4o]`
the code : `...[Speed/4o]`

means that the full package is 9 octets longs :
- the single octet for `[2]` - that has the value 2
- the ID on 4 octets `[ID/4o]`
- the speed on 4 octet `[Speed/4o]`
- the result is : `[2][ID/4o][Speed/4o]`
Because the code has `...` and that there is a global prefix, the complete code will be the concatenation of the prefixe and the rest.
**NB** a prefix can have a prefix

---

## TCP

First of all, at the beginning of all TCP request, there is 2 octets dedicated to the length of the request.
Prefix : 

### Server -> Client

