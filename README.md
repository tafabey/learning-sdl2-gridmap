learning-sdl2-gridmap

This project is purely for learning purposes. It is used to practice my C and SDL2 knowledge.

---

What does this program do?

Reads a 10x10 grid of numbers from the tile.txt file

The grid size can be changed before compilation using macros:

```c
#define ROWS 10
#define COLS 10
```

Each number represents a tile type:

0 → black (empty)

1 → white (wall)

3 → orange (lava)

---

Movement rules

The player cannot move into WALL (white) tiles

The player cannot move into LAVA (orange) tiles

LAVA tiles also deal damage to the player

---

Build & Run

Compile:
```bash
gcc learning-sdl2-gridmap.c -o gridmap.elf -lSDL2
```
Run:
```bash
./gridmap.elf
```