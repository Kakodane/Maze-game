# Maze-game

A console maze game made in C++. The player needs to get to the other end of the maze with the help of randomly spawning items, without the Minotaur defeating them.

## How the game works

- The maze is generated randomly on every run. The entrance (`U`) is in the top row and the exit (`I`) is in the bottom row.
- You play as the Robot (`R`), who starts right below the entrance. Your goal is to reach the cell directly above the exit.
- The Minotaur (`M`) wanders through the maze at random. After each of your moves it takes one step. If it is next to you (up, down, left or right), it catches you and you lose.
- Some cells contain items (`P`). Stepping on one gives you a random item that helps you for the next **3 moves**.
- Walking into a wall does not move you, but the turn is still used up and the Minotaur moves.

### Map legend

| Symbol | Meaning |
|--------|---------|
| `#` | Wall |
| `.` | Free path |
| `R` | You (the Robot) |
| `M` | The Minotaur |
| `P` | Item |
| `U` | Maze entrance |
| `I` | Maze exit |

### Items

An item is picked at random from the four below. Picking up a new item replaces the one that is active.

| Item | Effect (3 moves) |
|------|------------------|
| Fog of War | You only see the 3x3 area around yourself. The Minotaur still moves normally. |
| Sword | The Minotaur cannot defeat you. If you and the Minotaur meet, it is slain and you win. |
| Shield | The Minotaur only wanders randomly and cannot catch you. |
| Hammer | You can walk through walls. The Minotaur still moves normally. |

The active item is shown under the map as `Aktivan item: <name>`.

## Controls

Type a letter and press Enter:

| Key | Action |
|-----|--------|
| `w` | Move up |
| `a` | Move left |
| `s` | Move down |
| `d` | Move right |
| `q` | Quit the game |

Any other input is ignored and you are asked again.

## Getting started

### Requirements

- Windows
- Visual Studio 2022 with the "Desktop development with C++" workload (platform toolset v143)

### Build

```
git clone https://github.com/Kakodane/Maze-game.git
```

Open `Projekat.sln` in Visual Studio and build the solution (Ctrl+Shift+B).

### Run

The game takes three command-line arguments:

```
Projekat.exe <rows> <columns> <items>
```

| Argument | Meaning | Requirement |
|----------|---------|-------------|
| `rows` | Number of rows in the maze | greater than 15 |
| `columns` | Number of columns in the maze | greater than 15 |
| `items` | Number of items (`P`) placed in the maze | greater than 3 |

Example:

```
Projekat.exe 27 23 15
```

If the arguments are missing or invalid, the program prints an error message and exits.

To run from Visual Studio, set the arguments under Project > Properties > Debugging > Command Arguments (the Debug configuration is preset to `27 23 15`).

## Game result

When the game ends, the final state of the maze and the result are written to `Rezultat igre.txt` in the working directory. The result is one of:

- `Robot je pobedio` - the Robot won
- `Minotaur je pobedio` - the Minotaur won
- `Igra je prekinuta` - the game was quit with `q`

## Project structure

All source files are in the `Projekat` folder.

| File | Purpose |
|------|---------|
| `main.cpp` | Argument validation and the main game loop |
| `Game.h/.cpp` | Game state, player and Minotaur movement, item handling |
| `GameFlow.h/.cpp` | Runs one turn depending on the active item |
| `Maze.h/.cpp` | `Cell` and `Maze` classes and random maze generation |
| `Item.h/.cpp` | `Item` base class and the `FogOfWar`, `Sword`, `Shield` and `Hammer` classes |
| `ResFileInput.h/.cpp` | Writes the result to `Rezultat igre.txt` |

## Notes

- Before the game starts, the maze generator prints some debug output (generation time and intermediate maze states).
- In-game messages are in Serbian.
