#include "interactiveUI.hpp"
#include "enigma.hpp"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>
#include <set>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

using namespace std;

void showConfiguration(EnigmaConfig &config) {
    cout << "Plugboard connections: " << "[" << config.plugboardConnections << "]" << endl;
    cout << "Reflector type: " << config.reflector << endl;
    cout << "Rotor initial positions: " << config.rotorInitial << endl;

    cout << "Rotors: ";
    for(string s: config.rotorNames) {
        cout << s << " ";
    }
    cout << endl;

    waitForEnter();
}

void reflectorConfiguration(EnigmaConfig &config) {
    set<string> validReflectors = {"A", "B", "C"};

    while(true) {
        cout << "Expected input -> A" << endl;
        cout << "Possible reflectors -> [A, B, C]" << endl;
        cout << "Select reflector: ";

        string line;
        getline(cin, line);

        stringstream ss(line);
        string reflectorChoice;

        if(!(ss >> reflectorChoice)) {
            cout << "Error: No reflector entered" << endl;
            continue;
        }

        if(!validReflectors.count(reflectorChoice)) {
            cout << "Error: '" << reflectorChoice << "' is not a valid reflector" << endl;
            continue;
        }

        string extra;
        if(ss >> extra) {
            cout << "Error: Expected only one reflector, but received extra input" << endl;
            continue;
        }

        cout << "Reflector configured sucessfully" << endl;
        config.reflector = reflectorChoice;
        waitForEnter();
        break;
    }
}

void plugboardConfiguration(EnigmaConfig &config) {
    while(true) {
        cout << "Expected input -> AB CD EF" << endl;
        cout << "Possible pairs -> 2 different letters that has not been already connected" << endl;
        cout << "Select plugboard connections: ";

        string line;
        getline(cin, line);

        stringstream ss(line);
        string word;

        set<char> connectedChars;
        bool lineIsValid = true;
        
        while(ss >> word) {
            if(word.size() != 2) {
                cout << "Error: '" << word << "' is not a pair of letters" << endl;
                lineIsValid = false;
                break;
            }

            char c1 = toupper(word[0]), c2 = toupper(word[1]);

            if(c1 == c2) {
                cout << "Error: cannot connect a letter to itself ('" << word << "')" << endl;
                lineIsValid = false;
                break;
            }

            if(connectedChars.count(c1) || connectedChars.count(c2)) {
                cout << "Error: One of the letters in '" << word << "' is already connected in another pair." << endl;
                lineIsValid = false;
                break;
            }

            connectedChars.insert(c1);
            connectedChars.insert(c2);
        }

        if(!lineIsValid) {
            continue;
        }

        cout << "Plugboard configured sucessfully" << endl;
        config.plugboardConnections = line;
        waitForEnter();
        break;
    }
}

void rotorPositionConfiguration(EnigmaConfig &config) {
    while(true) {
        cout << "Expected input -> A A A" << endl;
        cout << "Possible positions -> letter A - Z" << endl;
        cout << "Select rotors initial positions: ";

        string line;
        getline(cin, line);

        stringstream ss(line);
        string word, positions = "";

        bool lineIsValid = true;
        
        while(ss >> word) {
            if(word.size() != 1 || !isalpha(word[0])) {
                cout << "Error: '" << word << "' is not a valid single alphabetic character for rotor position" << endl;
                lineIsValid = false;
                break;
            }

            positions += toupper(word[0]);
        }

        if(!lineIsValid) {
            continue;
        }

        if(positions.size() != config.rotorNames.size()) {
            cout << "Error: Rotor position does not match rotor amount - " << config.rotorNames.size() << " rotors <-> " << positions.size() << " positions." << endl;
            continue;
        }

        cout << "Rotors positions configured sucessfully" << endl;
        config.rotorInitial = positions;
        waitForEnter();
        break;
    }
}

void rotorConfiguration(EnigmaConfig &config) {
    set<string> validRotors = {"I", "II", "III", "IV", "V"};

    while(true) {
        cout << "Expected input -> I II III (minimum 3 rotors)" << endl;
        cout << "Possible rotors -> [I, II, III, IV, V]" << endl;
        cout << "Select rotors: ";

        string line;
        getline(cin, line);

        stringstream ss(line);
        string word;

        vector<string> chosenRotors;
        set<string> uniqueRotorsCheck;
        bool lineIsValid = true;
        
        while(ss >> word) {
            if(!validRotors.count(word)) {
                cout << "Error: '" << word << "' is not a valid rotor" << endl;
                lineIsValid = false;
                break;
            }

            if(uniqueRotorsCheck.count(word)) {
                cout << "Error: Rotor '" << word << "' was already chosen" << endl;
                lineIsValid = false;
                break;
            }

            chosenRotors.push_back(word);
            uniqueRotorsCheck.insert(word);
        }

        if(!lineIsValid) {
            continue;
        }

        if(chosenRotors.size() < 3) {
            cout << "Error: Expected minumum 3 rotors but got " << chosenRotors.size() << endl;
            continue;
        }

        cout << "Rotors configured sucessfully" << endl;
        config.rotorNames = chosenRotors;
        waitForEnter();
        break;
    }
}

void configurationMenu(int terminalWidth) {
    string bar(terminalWidth, '=');
    string title = "Configuration Menu";
    int padding = (terminalWidth - title.length()) / 2;

    string blankSpace = "";
    if(padding > 0) {blankSpace = string(padding, ' ');}

    cout << bar << endl;
    cout << blankSpace << title << endl;
    cout << bar << endl;
    cout << "1 - Rotors" << endl;
    cout << "2 - Rotors initial position" << endl;
    cout << "3 - Plugboard" << endl;
    cout << "4 - Reflector" << endl;
    cout << "5 - Show actual configuration" << endl;
    cout << "6 - Return" << endl;
    cout << bar << endl;
}

int selectConfigurationOption(Enigma &en, EnigmaConfig &config) {
    int option = -1;
    string input;
    cout << "Select option: ";
    getline(cin, input);

    try {
        option = stoi(input);
    } catch (const exception& e) {
    }

    if(input == "return") {option = 6;}

    switch (option) {
        case 1:
            rotorConfiguration(config);
            break;
        case 2:
            rotorPositionConfiguration(config);
            break;
        case 3:
            plugboardConfiguration(config);
            break;
        case 4:
            reflectorConfiguration(config);
            break;
        case 5:
            showConfiguration(config);
            break;
        case 6:
            try {
                en = Enigma(config);
            } catch (const std::exception& e) {
                std::cerr << "Error saving configuration - " << e.what() << std::endl;
                option = -1;
            }
            break;
        default:
            cout << "Wrong option: '" << input << "' is not a valid option." << endl;
            waitForEnter();
    }

    return option;
}

void handleConfiguration(Enigma &en, EnigmaConfig &config, int terminalWidth) {
    while(true) {
        configurationMenu(terminalWidth);
        int option = selectConfigurationOption(en, config);

        if(option == 6) {break;}
    }
}

void waitForEnter() {
    string input;
    cout << "Press anything to continue...";
    getline(cin, input);
}

int getTerminalWidth() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(!GetConsoleScreenBufferInfo(stdHandle, &csbi)) {
        return 80;
    }

    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}

void printPositions(Enigma en) {
    vector<char> positions = en.getRotorsPositions();
    for(char c: positions) {
        cout << c << " ";
    }
    cout << endl;
}

void displayLogo(int terminalWidth) {
    string bar(terminalWidth, '=');
    int logoLength = 117;
    int padding = (terminalWidth - logoLength) / 2;

    string blankSpace = "";
    if(padding > 0) {blankSpace = string(padding, ' ');}

    cout << endl;                                                                                                                
    cout << blankSpace << "                                          :*@@@@@@@@@@@@@@@@@@@@@@@@@@@#:                                           " << endl;
    cout << blankSpace << "                                    %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:                                    " << endl;
    cout << blankSpace << "                              #@@@@@@@@@@@@=   -@@@@             -@@@    -#@@@@@@@@@%:                              " << endl;
    cout << blankSpace << "                         .@@@@@@@@@@@@@@@@@    -@@@      %@@*      @@            @@@@@@@@#                          " << endl;
    cout << blankSpace << "                     :@@@@@@@@*        =@@@    -@@@    :@@@@@@     @@    -.          @@@@@@@@+                      " << endl;
    cout << blankSpace << "                  #@@@@@@@#             =@@    :@@%    -@@@@@@@@@@@@@    %@@    -     =@@@@@@@@@@.                  " << endl;
    cout << blankSpace << "               #@@@@@@  =@#    @@@@@    .@@    :@@%    -@@@@@@@@@@@@@    %@@    @@    =@@@@@   %@@@@-               " << endl;
    cout << blankSpace << "            *@@@@@=     -@%    @@@@@     @@    :@@@    -@@@@@@@@@@@@@    @@@    @@    *@@@=        @@@@*            " << endl;
    cout << blankSpace << "          @@@@@+     .@@@@@    @@@@@     @@    .@@@    -@@@@@@@@@@@@@    @@@   :@@    #@@#   *@%     @@@@@          " << endl;
    cout << blankSpace << "        :@@@@     =@@@@@@@@    @@@@@     @@    .@@@    -@@@@@@@@@@@@@    @@@   -@@    %@@    @@@@   .@@@@@@.        " << endl;
    cout << blankSpace << "          @@@    @@@@@@@@@@    @@@@@     @@    .@@@    =@@@@@@@@@@@@@    @@@   =@@    @@.   @@@@#   :@@@@           " << endl;
    cout << blankSpace << "           @@    +*++*@@@@@    @@@@@     @@    .@@@    =@@+=======%@@    @@@   +@@    @@    @@@@+   -@@@%           " << endl;
    cout << blankSpace << "          .@@         @@@@@    @@@@@.    @@    .@@@    =@-         @@    @@@   #@@    @@    @+      =@@@%           " << endl;
    cout << blankSpace << "          @@@.   @@@@@@@@@@    @@@@@.    @@     @@@    +@@@@@@@    @@    @@@   %@@    @@            *@@@@=          " << endl;
    cout << blankSpace << "       .@@@@@-   *@@@@@@@@@    @@@@@:    @@.    @@@    +@@@@@@@    @@    @@@   @@@    @@    #@@@    #@@@@@@         " << endl;
    cout << blankSpace << "         @@@@@      +@@@@@@    @@@@@:    @@.    @@@    +@@@@@@@    @@    @@%   @@@    @%   @@@@@    %@@@@           " << endl;
    cout << blankSpace << "           .@@@@@=       @@    @@@@@:    @@.    @@@    +@@@@@@@   .@@    @@%   @@@    @#   %@@@@ -@@@%              " << endl;
    cout << blankSpace << "               @@@@@@+   @@    %@@@@-    @@:    @@@    *@@@@@@@   .@@    @@#   @@@    @#   #@@@@@@*                 " << endl;
    cout << blankSpace << "                  -@@@@@@@@-   #@@@@-    @@-    @@@    *@@@@@@@   :@@    @@#   @@%    @@#@@@@@%.                    " << endl;
    cout << blankSpace << "                       @@@@@@@@@@@@@=    @@=    @@@    *@@@@@@%   :@%    @@*   @@# %@@@@@@%                         " << endl;
    cout << blankSpace << "                           :%@@@@@@@@%+: @@=    @@@               %@%    @@@+@@@@@@@@@-                             " << endl;
    cout << blankSpace << "                                  +@@@@@@@@@@%:.@@@@#            @@@@@@@@@@@@@@@-                                   " << endl;
    cout << blankSpace << "                                         -#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%=                                          " << endl;
}

void displayMenu(int terminalWidth) {
    string bar(terminalWidth, '=');
    string title = "Main Menu";
    int padding = (terminalWidth - title.length()) / 2;

    string blankSpace = "";
    if(padding > 0) {blankSpace = string(padding, ' ');}

    cout << bar << endl;
    cout << blankSpace << title << endl;
    cout << bar << endl;
    cout << "1 - Enigma configuration (will reset your enigma machine)" << endl;
    cout << "2 - Encrypt text" << endl;
    cout << "3 - Encrypt characters showing steps" << endl;
    cout << "4 - Reset enigma state" << endl;
    cout << "5 - Exit" << endl;
    cout << bar << endl;
}

void textEncryption(Enigma &en) {
    string input, output;
    cout << "Enter text to encrypt: ";
    getline(cin, input);
    output = en.encodeText(input);
    cout << output << endl;
    waitForEnter();
}

void encryptionSteps(Enigma &en) {
    while(true) {
        int terminalWidth = getTerminalWidth();
        string bar(terminalWidth, '=');
        cout << bar << endl;
        cout << "Rotors positions: ";
        printPositions(en);
        cout << "<- write 'return' to go back" << endl;
        cout << "Type a letter to encrypt: ";

        string letter;
        getline(cin, letter);

        transform(letter.begin(), letter.end(), letter.begin(), ::tolower);
        if(letter == "return")
            break;

        stringstream ss(letter);
        string readLetter;

        if(!(ss >> readLetter)) {
            cout << "Error: no letter typed" << endl;
            continue;
        }

        string extra;
        if(ss >> extra) {
            cout << "Error: Expected only one letter, but received extra input" << endl;
            continue;
        }

        if(!isalpha(readLetter[0])) {
            cout << "Error: '" << readLetter << "' is not a valid character, only allowed letters A-Z" << endl;
            continue;
        }

        char encryptedLetter = en.press(readLetter[0], true);
        cout << readLetter[0] << " encrypted to " << encryptedLetter << endl;

        string again;
        cout << "Encrypt another character? [Y/n]: ";
        getline(cin, again);

        transform(again.begin(), again.end(), again.begin(), ::tolower);
        if(again == "n" || again == "no") {
            break;
        }
    }
}

int selectOption(Enigma &en, EnigmaConfig &config, int terminalWidth) {
    int option = -1;
    string input;
    cout << "Select option: ";
    getline(cin, input);

    if(input == "exit") {return 5;}

    try {
        option = stoi(input);
    } catch (const exception& e) {
    }

    switch (option) {
        case 1:
            handleConfiguration(en, config, terminalWidth);
            break;
        case 2:
            textEncryption(en);
            break;
        case 3:
            encryptionSteps(en);
            break;
        case 4:
            try {
                en = Enigma(config);
                cout << "Enigma machine rotors position back from configurated state (positions: " + config.rotorInitial +")" << endl;
            } catch (const std::exception& e) {
                std::cerr << "Error saving configuration - " << e.what() << std::endl;
                option = -1;
            }
            waitForEnter();
            break;
        case 5:
            cout << "exiting..." << endl;
            break;
        default:
            cout << "Wrong option: '" << input << "' is not a valid option." << endl;
            waitForEnter();
    }

    return option;
}

void interactiveMode() { 
    EnigmaConfig config;
    Enigma en(config);

    while(true) {
        int currentWidth = getTerminalWidth();
        if(currentWidth >= 130) {displayLogo(currentWidth);}
        displayMenu(currentWidth);
        int option = selectOption(en, config, currentWidth);

        if(option == 5) {break;}
    }
}