# car_collision_game

A 2D dodge game written in C using the [raylib](https://www.raylib.com) library. Drive your car, avoid the enemy cars coming down the road, and try to beat your best score on each difficulty.

## Features

- Three game states: menu, playing, and game over
- Three difficulty levels (Easy, Medium, Hard) with different enemy counts and speeds
- Enemy cars spawn in three lanes and move diagonally down the screen
- Overlap-free spawning: each enemy tries up to 20 random positions and keeps the first free one
- Random enemy colors (blue, green, yellow) using texture tinting
- Hitboxes smaller than the sprites, so collisions match what you see
- Player stays inside the screen on all four sides
- Separate high score for each difficulty, saved to a text file

## Controls

| Key | Action |
|---|---|
| `1` / `2` / `3` | Choose Easy / Medium / Hard (on the menu) |
| Arrow keys | Move the car |
| `Enter` | Return to the menu after game over |

## Difficulty Levels

| Level | Enemies | Speed |
|---|---|---|
| Easy | 5 | 3 |
| Medium | 8 | 4 |
| Hard | 12 | 5 |

## How to Play

1. Pick a difficulty on the menu.
2. Dodge the enemy cars with the arrow keys.
3. You earn 1 point for each enemy car that passes the bottom of the screen.
4. If your car touches an enemy, the game ends. If your score beats the record for that difficulty, it is saved.

## Project Structure

```
.
├── main.c          # Game loop, game states, menu, scoring, high score file handling
├── car.c           # Car functions: create, draw, move, respawn, hitbox
├── car.h           # car struct, GameState enum, function declarations
├── player.png      # Player car image
├── enemy.png       # Enemy car image
└── highScore.txt   # Created automatically after the first record is saved
```

## Requirements

- A C compiler (MSVC, GCC or Clang)
- [raylib](https://www.raylib.com) installed

## Build and Run

### Visual Studio (Windows)

1. Create a C project and add `main.c`, `car.c` and `car.h`.
2. Install and link raylib (for example with vcpkg or the official raylib installer).
3. Place `player.png` and `enemy.png` in the project's working directory (usually the project folder).
4. Build and run.

`main.c` starts with `#define _CRT_SECURE_NO_WARNINGS` so Visual Studio accepts `fopen`, `fscanf` and `fprintf`.

### GCC / MinGW (Windows)

```bash
gcc main.c car.c -o CarGame -lraylib -lopengl32 -lgdi32 -lwinmm
```

### GCC (Linux)

```bash
gcc main.c car.c -o CarGame -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

Run the game from the folder that contains `player.png` and `enemy.png`, because the images are loaded using relative paths:

```bash
./CarGame
```

## High Scores

The best score for each difficulty is stored in `highScore.txt`, one number per line:

```
12   <- Easy
8    <- Medium
3    <- Hard
```

If the file does not exist, all scores start at 0. Delete the file to reset your records.

## How It Works

- **Game states:** an `enum GameState { MENU, PLAYING, GAME_END }` decides what runs and what is drawn each frame.
- **Spawning:** `EnemyRespawn` picks a lane and a height above the screen, enlarges the car's box by 20 pixels, and checks it against the other enemies. If it overlaps, it tries again (up to 20 times).
- **Hitbox:** `CarGetRect` trims 15% from the sides and 10% from the top and bottom of the sprite to remove transparent padding.
- **File handling:** the three high scores are loaded at startup and all three are written back whenever a record is beaten.

## Known Limitations

- Spawn checking guarantees free space only at spawn time, so enemies moving in different directions can still cross paths.
- If 20 attempts fail (possible on Hard), an enemy may spawn overlapping another.
- Hitboxes are rectangles, not pixel-perfect.
- No sound, pause menu or gamepad support.

## Future Improvements

- Sound effects and music
- Pause menu
- Top 5 scores per difficulty
- Speed that increases as the score grows
- Power-ups and lives

## Notes

`CarDraw` in `car.c` contains a debug line that draws the hitbox outline:

```c
DrawRectangleLinesEx(CarGetRect(c), 2, RED);
```
## License

Add a license if you want one (for example MIT), or remove this section
