cmake_minimum_required(VERSION 3.12)
project(Asteroids VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(MACOSX_BUNDLE TRUE)

# Diagnostic information about the system
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Processor: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

# Set option to use SFML
option(USE_SFML "Try to use SFML libraries" OFF)

# Source files
set(SOURCES
    src/main.cpp
)

if(USE_SFML)
    # Add all source files when using SFML
    list(APPEND SOURCES
        src/Game.cpp
        src/Player.cpp
        src/Asteroid.cpp
        src/Bullet.cpp
        src/Entity.cpp
        src/Particle.cpp
        src/ResourceManager.cpp
        src/AudioManager.cpp
        src/Collision.cpp
        src/UI.cpp
    )
    
    # Header files
    set(HEADERS
        include/Game.hpp
        include/Player.hpp
        include/Asteroid.hpp
        include/Bullet.hpp
        include/Entity.hpp
        include/Particle.hpp
        include/ResourceManager.hpp
        include/AudioManager.hpp
        include/Collision.hpp
        include/UI.hpp
        include/Constants.hpp
    )
endif()

# Create executable
add_executable(Asteroids ${SOURCES})

# Set include directories
target_include_directories(Asteroids PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link libraries based on configuration
if(USE_SFML)
    # Manually specify SFML libraries - direct approach without using find_package
    message(STATUS "Attempting to use SFML libraries")
    
    # Hard-code the paths for Homebrew SFML on macOS
    if(APPLE)
        set(SFML_DIR "/opt/homebrew/lib/cmake/SFML")
        set(SFML_INCLUDE_DIR "/opt/homebrew/include")
        set(SFML_LIB_DIR "/opt/homebrew/lib")
        
        message(STATUS "Setting SFML paths for macOS: ${SFML_DIR}")
        message(STATUS "Include: ${SFML_INCLUDE_DIR}")
        message(STATUS "Lib: ${SFML_LIB_DIR}")
        
        # Include SFML header files
        target_include_directories(Asteroids PRIVATE ${SFML_INCLUDE_DIR})
        
        # Try to find the libraries directly
        find_library(SFML_SYSTEM_LIB sfml-system PATHS ${SFML_LIB_DIR} NO_DEFAULT_PATH)
        find_library(SFML_WINDOW_LIB sfml-window PATHS ${SFML_LIB_DIR} NO_DEFAULT_PATH)
        find_library(SFML_GRAPHICS_LIB sfml-graphics PATHS ${SFML_LIB_DIR} NO_DEFAULT_PATH)
        find_library(SFML_AUDIO_LIB sfml-audio PATHS ${SFML_LIB_DIR} NO_DEFAULT_PATH)
        
        message(STATUS "SFML System: ${SFML_SYSTEM_LIB}")
        message(STATUS "SFML Window: ${SFML_WINDOW_LIB}")
        message(STATUS "SFML Graphics: ${SFML_GRAPHICS_LIB}")
        message(STATUS "SFML Audio: ${SFML_AUDIO_LIB}")
        
        # Link to found libraries
        if(SFML_SYSTEM_LIB AND SFML_WINDOW_LIB AND SFML_GRAPHICS_LIB AND SFML_AUDIO_LIB)
            target_link_libraries(Asteroids ${SFML_SYSTEM_LIB} ${SFML_WINDOW_LIB} ${SFML_GRAPHICS_LIB} ${SFML_AUDIO_LIB})
            target_compile_definitions(Asteroids PRIVATE USE_SFML)
        else()
            message(WARNING "Some SFML libraries not found, disabling SFML")
            target_compile_definitions(Asteroids PRIVATE NO_GRAPHICS)
        endif()
    else()
        message(WARNING "SFML path handling only implemented for macOS")
        target_compile_definitions(Asteroids PRIVATE NO_GRAPHICS)
    endif()
else()
    message(STATUS "SFML integration disabled")
    target_compile_definitions(Asteroids PRIVATE NO_GRAPHICS)
endif()

# Copy resources to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# macOS specific settings
if(APPLE)
    # Enable high-DPI support
    target_compile_definitions(Asteroids PRIVATE "GL_SILENCE_DEPRECATION")
    
    # Set minimum macOS version to ensure compatibility with macOS 15.0 Sequoia
    set(CMAKE_OSX_DEPLOYMENT_TARGET "15.0" CACHE STRING "Minimum macOS deployment version")
    
    # Create a proper app bundle
    set_target_properties(Asteroids PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.example.asteroids"
        MACOSX_BUNDLE_BUNDLE_NAME "Asteroids"
        MACOSX_BUNDLE_BUNDLE_VERSION "1.0"
        MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0"
    )
endif()

# Copy the resources folder into the bundle's Resources folder
install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app/Contents/Resources)
