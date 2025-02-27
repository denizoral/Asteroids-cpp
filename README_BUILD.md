# Asteroids Game Build Guide

This document provides instructions for building and running the Asteroids game using the provided build script.

## Using the Build Script

The project includes a convenient build script (`build.sh`) that makes it easy to clean, configure, build, and run the game.

### First, make the script executable:

```bash
chmod +x build.sh
```

### Basic Usage:

```bash
./build.sh [options]
```

### Options:

- `-h, --help`: Show help message
- `-c, --clean`: Clean the build directory before building
- `-n, --no-sfml`: Build without SFML support (text-only mode)
- `-r, --run`: Run the game after building
- `-v, --verbose`: Show verbose output
- `--no-build`: Configure only, don't build

### Common Examples:

1. **Clean, build with SFML, and run the game:**
   ```bash
   ./build.sh -c -r
   ```

2. **Build without SFML (text-only mode):**
   ```bash
   ./build.sh -n
   ```

3. **Clean and configure, but don't build:**
   ```bash
   ./build.sh -c --no-build
   ```

4. **Show verbose output during build:**
   ```bash
   ./build.sh -v
   ```

## Troubleshooting

If you encounter issues with SFML, try the following:

1. Ensure SFML is installed correctly:
   ```bash
   brew info sfml
   ```

2. Try building without SFML to see if that works:
   ```bash
   ./build.sh -n
   ```

3. If you see errors about SFML API changes, you might need to update the code for compatibility with your SFML version.

## Manual Build Process

If you prefer not to use the script, here are the manual commands:

```bash
# Create and enter build directory
mkdir -p build
cd build

# Configure with SFML
cmake .. -DUSE_SFML=ON

# Configure without SFML
cmake ..

# Build
cmake --build .

# Run (macOS)
./Asteroids.app/Contents/MacOS/Asteroids
```
