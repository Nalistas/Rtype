# Protocole

First of all, all requests start with the size of the request on 1 octet !

`[SIZE]`

## Protocole Server -> Client

the protocol server to client is 4 instructions :
Create entity - opcode = 1
Delete entity - opcode = 2
Update entity - opcode = 3
Define action - opcode = 4

all on 1 Byte

so we have :
`[SIZE][OPCODE]`
pour l'instant le tout sur 2 octet

### Create/Update
Those 2 instructions have 4 possibilities, create or update :
1. un Background
2. une musique
3. un son
4. un Sprite

Each on has the EntityCode of their number up and is coded on 1 Byte.

`[SIZE][OPCODE][ENTITY TYPE]`

the following data are specific to each entity type.

**Let's define some notation**
"/4b" means it is coded on 4 Bytes
"/1b" means on 1 Byte

#### Background
**opcode: 1**
the background contain the following information :
- speed: the speed of the background in case of movement `[SPEED /1b]`
- direction: if it is horizontal (x movement) or vertical (y movement) `[DIR 1=Y:2=X /1b]`
- resize: if it must be resized `[RESIZE 1/0 /1b]`
- repeat: if it must be repeated `[REPEAT 1/0 /1b]`
- path: the path. We suppose that the image is already on the client `[Path on a undetermined size]`

for summarize, to create or Update a Background:

`[SIZE][1 or 3][SPEED][DIRECTION][RESIZE][REPEAT][PATH...]`
for a total size of 5 + size of path

#### Sprite
**opcode: 4**
The Sprite contains the following information :
- `speed_x` : la vitesse du sprite sur l'axe X `[SPEED_X /1b]`
- `speed_y` : la vitesse du sprite sur l'axe Y `[SPEED_Y /1b]`
- `pos_x` : la position du sprite sur l'axe X `[POS_X /4b]`
- `pos_y` : la position du sprite sur l'axe Y `[POS_Y /4b]`
- `size_x` : la taille du sprite sur l'axe X `[SIZE_X /4b]`
- `size_y` : la taille du sprite sur l'axe Y `[SIZE_Y /4b]`
- `text_rect_width` : la largeur de la zone de texte (rectangle de sprite) `[TEXT_RECT_WIDTH /4b]`
- `text_rect_height` : la hauteur de la zone de texte `[TEXT_RECT_HEIGHT /4b]`
- `offset_x` : décalage du sprite sur l'axe X `[OFFSET_X /4b]`
- `offset_y` : décalage du sprite sur l'axe Y `[OFFSET_Y /4b]`
- `nb_frames` : nombre de frames pour l'animation du sprite `[NB_FRAMES /1b]`
For summarize, to create or Update a Sprite:

`[SIZE][4][SPEED_X][SPEED_Y][POS_X][POS_Y][SIZE_X][SIZE_Y][TEXT_RECT_WIDTH][TEXT_RECT_HEIGHT][OFFSET_X][OFFSET_Y][NB_FRAMES][MS_PER_FRAME][AUTO_DESTROY][PATH...]`
for a total size of 24 + size of path

#### Music
**opcode: 2**
The Music contains the following information :
- `path` : the path to the music file `[PATH / undetermined size]`

To create or update Music:

`[SIZE][2][PATH...]`
for a total size of 2 + size of path

#### Sound
**opcode: 3**
The Sound contains the following information :
- `path` : the path to the sound file `[PATH / undetermined size]`

To create or update Sound:

`[SIZE][3][PATH...]`
for a total size of 2 + size of path

#### Action Definition
**opcode: 4**
The Action contains the following information :
- `key` : the key associated with the action `[KEY /4b]`, the key associated is based on raylib. For a list of key codes used in raylib, please refer to the official [raylib keycodes documentation on GitHub](https://github.com/raysan5/raylib/blob/master/src/rlgl.h#L55).
- `id_action` : a unique identifier for the action `[ID_ACTION /4b]` 
- `state` : the state of the key `[STATE 0=Pressed:1=Released /1b]`

To define an Action:

`[SIZE][4][KEY][ID_ACTION][STATE]`
for a total size of 11

## Protocole Client -> Server

The protocol from the client to the server follows a similar structure with some key differences based on the communication needs. Here are the details:

### Client to Server Action Definition
When the client wants to send an action (such as a key press or mouse event), it sends the following:

`[SIZE][ID_ACTION /4b][MOUSE_POS /4b][ID_ACTION /4b]`

here, the ID_ACTION is the id action given by the server during the Action definition

---

This markdown document defines the protocol for communication between the server and client. Each message starts with a size header, followed by the operation type (opcode), and entity-specific data. You can now use this structure to design the communication between the server and client for all relevant actions.
