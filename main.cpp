#include "enigma.hpp"
#include "interactiveUI.hpp"
#include "argumentUI.hpp"

#ifdef _WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif

int main(int argc, char* argv[]) {
    if(argc > 1) {
        // argumentMode(argc, argv);
    } else {
         bool isInteractiveTerminal;

        #ifdef _WIN32
            isInteractiveTerminal = _isatty(_fileno(stdin));
        #else
            isInteractiveTerminal = isatty(STDIN_FILENO);
        #endif

        if(isInteractiveTerminal) {
            interactiveMode();
        } else {
            EnigmaConfig config;
            Enigma en(config);

            processStream(en, std::cin, std::cout);
        }
    }

    return 0;
}