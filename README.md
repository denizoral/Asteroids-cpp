# Asteroids

A modern C++ implementation of the classic Asteroids game for macOS Sequoia 15.0.

## Requirements

- macOS Sequoia 15.0 or newer
- CMake 3.12 or newer
- SFML 2.5 or newer

## Building the Game

### Installing Dependencies

First, install the required dependencies using Homebrew:

```bash
brew install cmake
brew install sfml
```

### Building the Project

1. Navigate to the project directory:

```bash
cd /path/to/spaceship
```

2. Create a build directory and navigate to it:

```bash
mkdir build
cd build
```

3. Configure with CMake:

```bash
cmake ..
```

4. Build the project:

```bash
cmake --build .
```

5. Run the game:

```bash
./Asteroids
```

## Controls

- **Arrow Keys / WASD**: Control the spaceship
- **Space**: Fire bullets
- **P**: Pause/Resume game

## Game Rules

- Destroy asteroids to earn points
- Large asteroids split into medium ones, and medium ones split into small ones
- Avoid colliding with asteroids
- You have 3 lives
- Game ends when all lives are lost

## File Structure

- `src/`: Source code files
- `include/`: Header files
- `resources/`: Game resources (fonts, sounds)

## Credits

This game is inspired by the classic Atari Asteroids game from 1979.
