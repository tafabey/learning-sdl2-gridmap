# learning-sdl2-gridmap

This project is an SDL2 practice written in C.

## What does this project do?

- Reads a grid of `0` and `1` values from the `tile.txt` file  
  (default size is 10x10, can be changed before compilation using the
  `COLS` and `ROWS` macros in the source code).
- Renders the grid on the screen:
  - `0` values are drawn as black tiles
  - `1` values are drawn as white tiles
- Draws a brown square (player).
- Allows the player to move only on white tiles and prevents movement
  into black tiles.

## Build

SDL2 development libraries must be installed on your system.

On Debian / Ubuntu based systems:
```bash
sudo apt install libsdl2-dev
```

Compile:
```bash
gcc learning-sdl2-gridmap.c -o gridmap.elf `sdl2-config --cflags --libs`
```

## Run

Make the file executable:
```bash
chmod +x gridmap.elf
```

Run the program:
```bash
./gridmap.elf
```
