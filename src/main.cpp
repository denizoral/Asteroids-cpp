#include <iostream>
#include <exception>

#if defined(USE_SFML)
#include "Game.hpp"
#endif

int main()
{
    try {
#if defined(NO_GRAPHICS)
        std::cout << "Asteroids Game" << std::endl;
        std::cout << "------------------" << std::endl;
        std::cout << "SFML graphics library was not found or disabled during compilation." << std::endl;
        
        std::cout << "\nTo install SFML:" << std::endl;
        std::cout << "  brew install sfml" << std::endl;
        
        std::cout << "\nTo build with SFML support:" << std::endl;
        std::cout << "  cd build" << std::endl;
        std::cout << "  cmake .. -DUSE_SFML=ON" << std::endl;
        std::cout << "  cmake --build ." << std::endl;
        
        // Diagnostic information about installed libraries
        std::cout << "\nLibrary paths to check:" << std::endl;
        std::cout << "  /opt/homebrew/lib/libsfml-system.dylib" << std::endl;
        std::cout << "  /opt/homebrew/lib/libsfml-window.dylib" << std::endl;
        std::cout << "  /opt/homebrew/lib/libsfml-graphics.dylib" << std::endl;
        std::cout << "  /opt/homebrew/lib/libsfml-audio.dylib" << std::endl;
        
        std::cout << "\nCheck if these files exist. If not, SFML might need to be installed." << std::endl;
        
        return EXIT_SUCCESS;
#else
        // When SFML is available
        Game game;
        game.run();
#endif
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "Unknown fatal error!" << std::endl;
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
