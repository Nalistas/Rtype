
# R-Type - EPITECH 3rd Year Project

## Overview
R-Type is a **2D shoot'em up** game inspired by the classic *R-Type*, designed and developed by a group of students from EPITECH in their third year. This project incorporates **multiplayer gaming**, **networking**, and **real-time game mechanics**. The game features a **client-server architecture** that enables players to connect to a central server, join rooms, and engage in fast-paced, multiplayer battles.

## Features

- **Multiplayer**: Real-time multiplayer gameplay using TCP and UDP protocols.
- **Client-Server Architecture**: The server handles game state synchronization and player management, while the client provides the interactive gameplay interface.
- **Graphics**: Developed using the **Raylib** for rendering and input management.
- **Network Communication**: The game uses **custom protocols** (UDP for real-time game communication).
- **Game Mechanics**: Includes classic elements of the shoot'em up genre such as enemy waves, power-ups, and challenging levels.

## Technologies Used
- **Languages**: C++
- **Libraries**: Raylib for graphics, CMake for build configuration, and custom networking libraries.
- **Tools**: Git for version control, CMake for project build management.

## Setup

### Prerequisite

#### For Windows, you need to have:
- [Git](https://git-scm.com/) (version >= 2.30 recommended)
- [CMake](https://cmake.org/download/) (version >= 3.15 recommended)
- [MinGW-w64](https://mingw-w64.org/doku.php/download) (can be installed with [MSYS2](https://www.msys2.org/))

---

### For Linux users:
- [Git](https://git-scm.com/) (version >= 2.30 recommended)
- [CMake](https://cmake.org/download/) (version >= 3.15 recommended)
- [g++](https://gcc.gnu.org/)

---


1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/Rtype.git
    cd Rtype
    ```

3. **Build the project**:
    to build the project, you can simply launch `compile.sh`for linux or `compile.bat` for windows
    the cmakelists will handle the foreign package byt themselves

4. **Running the game**:
    - **Server**: To start the server, specify TCP and UDP ports:
    ```bash
    ./r-type_server <TCP_PORT>
    ```
    by default, the server starts on port 2000
    - **Client**: To run the client, simply launch:
    ```bash
    ./r-type_client
    ```

## How to Play
1. Launch the server with the desired ports.
2. Launch the client and enter the server IP and port to connect.
3. Once connected, select or create a room to start the game.
4. Play through various levels, defeat enemies, and collect power-ups.

## Contributing
If you'd like to contribute to this project, feel free to fork the repository, create an issue, or submit a pull request with your proposed changes.

## Documentation
The documentation is automatically generated by Doxygen and is on the branch gh-pages
