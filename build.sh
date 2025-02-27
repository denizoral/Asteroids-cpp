#!/bin/bash

# Colors for terminal output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Project directories
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${PROJECT_DIR}/build"

# Default values
USE_SFML=ON
CLEAN=false
BUILD=true
RUN=false
VERBOSE=false

# Function to show usage
show_help() {
    echo -e "${BLUE}Asteroids Game Build Script${NC}"
    echo
    echo "Usage: ./build.sh [options]"
    echo
    echo "Options:"
    echo "  -h, --help        Show this help message"
    echo "  -c, --clean       Clean the build directory before building"
    echo "  -n, --no-sfml     Build without SFML support (text-only mode)"
    echo "  -r, --run         Run the game after building"
    echo "  -v, --verbose     Show verbose output"
    echo "  --no-build        Configure only, don't build"
    echo
    echo "Examples:"
    echo "  ./build.sh -c -r        # Clean, build with SFML, and run"
    echo "  ./build.sh -n           # Build without SFML"
    echo "  ./build.sh --no-build   # Configure only, don't build"
    echo
}

# Parse command-line arguments
while [[ $# -gt 0 ]]; do
    case "$1" in
        -h|--help)
            show_help
            exit 0
            ;;
        -c|--clean)
            CLEAN=true
            shift
            ;;
        -n|--no-sfml)
            USE_SFML=OFF
            shift
            ;;
        -r|--run)
            RUN=true
            shift
            ;;
        -v|--verbose)
            VERBOSE=true
            shift
            ;;
        --no-build)
            BUILD=false
            shift
            ;;
        *)
            echo -e "${RED}Unknown option: $1${NC}"
            show_help
            exit 1
            ;;
    esac
done

# Create build directory if it doesn't exist
if [ ! -d "${BUILD_DIR}" ]; then
    echo -e "${BLUE}Creating build directory...${NC}"
    mkdir -p "${BUILD_DIR}"
fi

# Clean build directory if requested
if [ "$CLEAN" = true ]; then
    echo -e "${YELLOW}Cleaning build directory...${NC}"
    rm -rf "${BUILD_DIR:?}"/*
    if [ $? -ne 0 ]; then
        echo -e "${RED}Failed to clean build directory!${NC}"
        exit 1
    fi
    echo -e "${GREEN}Build directory cleaned successfully.${NC}"
fi

# Change to build directory
cd "${BUILD_DIR}" || { echo -e "${RED}Failed to change to build directory!${NC}"; exit 1; }

# Configure the project
echo -e "${BLUE}Configuring project with USE_SFML=${USE_SFML}...${NC}"
if [ "$VERBOSE" = true ]; then
    cmake .. -DUSE_SFML=${USE_SFML}
else
    cmake .. -DUSE_SFML=${USE_SFML} > /dev/null
fi

if [ $? -ne 0 ]; then
    echo -e "${RED}Configuration failed!${NC}"
    exit 1
fi
echo -e "${GREEN}Configuration successful.${NC}"

# Build the project if requested
if [ "$BUILD" = true ]; then
    echo -e "${BLUE}Building project...${NC}"
    if [ "$VERBOSE" = true ]; then
        cmake --build .
    else
        cmake --build . > /dev/null
    fi

    if [ $? -ne 0 ]; then
        echo -e "${RED}Build failed!${NC}"
        exit 1
    fi
    echo -e "${GREEN}Build successful.${NC}"
fi

# Run the game if requested
if [ "$RUN" = true ]; then
    echo -e "${BLUE}Running Asteroids game...${NC}"
    if [ -d "${BUILD_DIR}/Asteroids.app" ]; then
        # Handle macOS app bundle
        echo -e "${YELLOW}Using the binary inside the app bundle for better console output...${NC}"
        "${BUILD_DIR}/Asteroids.app/Contents/MacOS/Asteroids"
    elif [ -x "${BUILD_DIR}/Asteroids" ]; then
        # Handle direct executable
        "${BUILD_DIR}/Asteroids"
    else
        echo -e "${RED}Executable not found! Did the build succeed?${NC}"
        exit 1
    fi
fi

echo -e "${GREEN}All operations completed successfully.${NC}"
