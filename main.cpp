#include "interactiveUI.hpp"
#include "argumentUI.hpp"

#ifdef _WIN32
    #include <io.h>
#else
    #include <unistd.h>
#endif

int main(int argc, char* argv[]) {
    bool stdinIsTty, stdoutIsTty;

    #ifdef _WIN32
        stdinIsTty = _isatty(_fileno(stdin));
        stdoutIsTty = _isatty(_fileno(stdout));
    #else
        stdinIsTty = isatty(STDIN_FILENO);
        stdoutIsTty = isatty(STDOUT_FILENO);
    #endif

    if(argc == 1 && stdinIsTty && stdoutIsTty) {
        interactiveMode();
    } else {
        argumentMode(argc, argv, stdinIsTty);
    }

    return 0;
}