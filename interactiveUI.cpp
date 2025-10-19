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

    pause();
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
            cout << "Error: '" << reflectorChoice << "is not a valid reflector" << endl;
            continue;
        }

        string extra;
        if(ss >> extra) {
            cout << "Error: Expected only one reflector, but received extra input" << endl;
            continue;
        }

        cout << "Reflector configured sucessfully" << endl;
        config.reflector = reflectorChoice;
        pause();
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
        pause();
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
        pause();
        break;
    }
}

void rotorConfiguration(EnigmaConfig &config) {
    set<string> validRotors = {"I", "II", "III", "IV", "V"};

    while(true) {
        cout << "Expected input -> I II III" << endl;
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
                cout << "Error: '" << word << "is not a valid rotor" << endl;
                lineIsValid = false;
                break;
            }

            if(uniqueRotorsCheck.count(word)) {
                cout << "Error: Rotor '" << word << "was already chosen" << endl;
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
        pause();
        break;
    }
}

void configurationMenu() {
    cout << "====================================================================================================================" << endl;
    cout << "                                            Configuration Menu" << endl;
    cout << "====================================================================================================================" << endl;
    cout << "1 - Rotors" << endl;
    cout << "2 - Rotors initial position" << endl;
    cout << "3 - Plugboard" << endl;
    cout << "4 - Reflector" << endl;
    cout << "5 - Show actual configuration" << endl;
    cout << "6 - Return" << endl;
    cout << "====================================================================================================================" << endl;
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
            pause();
    }

    return option;
}

void handleConfiguration(Enigma &en, EnigmaConfig &config) {
    while(true) {
        configurationMenu();
        int option = selectConfigurationOption(en, config);

        if(option == 6) {break;}
    }
}

void pause() {
    string input;
    cout << "Press anything to continue...";
    getline(cin, input);
}

void printPositions(Enigma en) {
    vector<char> positions = en.getRotorsPositions();
    for(char c: positions) {
        cout << c << " ";
    }
    cout << endl;
}

void displayLogo() {
    cout << endl;                                                                                                                
    cout << "                                          :*@@@@@@@@@@@@@@@@@@@@@@@@@@@#:                                           " << endl;
    cout << "                                    %@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:                                    " << endl;
    cout << "                              #@@@@@@@@@@@@=   -@@@@             -@@@    -#@@@@@@@@@%:                              " << endl;
    cout << "                         .@@@@@@@@@@@@@@@@@    -@@@      %@@*      @@            @@@@@@@@#                          " << endl;
    cout << "                     :@@@@@@@@*        =@@@    -@@@    :@@@@@@     @@    -.          @@@@@@@@+                      " << endl;
    cout << "                  #@@@@@@@#             =@@    :@@%    -@@@@@@@@@@@@@    %@@    -     =@@@@@@@@@@.                  " << endl;
    cout << "               #@@@@@@  =@#    @@@@@    .@@    :@@%    -@@@@@@@@@@@@@    %@@    @@    =@@@@@   %@@@@-               " << endl;
    cout << "            *@@@@@=     -@%    @@@@@     @@    :@@@    -@@@@@@@@@@@@@    @@@    @@    *@@@=        @@@@*            " << endl;
    cout << "          @@@@@+     .@@@@@    @@@@@     @@    .@@@    -@@@@@@@@@@@@@    @@@   :@@    #@@#   *@%     @@@@@          " << endl;
    cout << "        :@@@@     =@@@@@@@@    @@@@@     @@    .@@@    -@@@@@@@@@@@@@    @@@   -@@    %@@    @@@@   .@@@@@@.        " << endl;
    cout << "          @@@    @@@@@@@@@@    @@@@@     @@    .@@@    =@@@@@@@@@@@@@    @@@   =@@    @@.   @@@@#   :@@@@           " << endl;
    cout << "           @@    +*++*@@@@@    @@@@@     @@    .@@@    =@@+=======%@@    @@@   +@@    @@    @@@@+   -@@@%           " << endl;
    cout << "          .@@         @@@@@    @@@@@.    @@    .@@@    =@-         @@    @@@   #@@    @@    @+      =@@@%           " << endl;
    cout << "          @@@.   @@@@@@@@@@    @@@@@.    @@     @@@    +@@@@@@@    @@    @@@   %@@    @@            *@@@@=          " << endl;
    cout << "       .@@@@@-   *@@@@@@@@@    @@@@@:    @@.    @@@    +@@@@@@@    @@    @@@   @@@    @@    #@@@    #@@@@@@         " << endl;
    cout << "         @@@@@      +@@@@@@    @@@@@:    @@.    @@@    +@@@@@@@    @@    @@%   @@@    @%   @@@@@    %@@@@           " << endl;
    cout << "           .@@@@@=       @@    @@@@@:    @@.    @@@    +@@@@@@@   .@@    @@%   @@@    @#   %@@@@ -@@@%              " << endl;
    cout << "               @@@@@@+   @@    %@@@@-    @@:    @@@    *@@@@@@@   .@@    @@#   @@@    @#   #@@@@@@*                 " << endl;
    cout << "                  -@@@@@@@@-   #@@@@-    @@-    @@@    *@@@@@@@   :@@    @@#   @@%    @@#@@@@@%.                    " << endl;
    cout << "                       @@@@@@@@@@@@@=    @@=    @@@    *@@@@@@%   :@%    @@*   @@# %@@@@@@%                         " << endl;
    cout << "                           :%@@@@@@@@%+: @@=    @@@               %@%    @@@+@@@@@@@@@-                             " << endl;
    cout << "                                  +@@@@@@@@@@%:.@@@@#            @@@@@@@@@@@@@@@-                                   " << endl;
    cout << "                                         -#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%=                                          " << endl;
}

void displayMenu() {
    cout << "====================================================================================================================" << endl;
    cout << "                                                  Main Menu" << endl;
    cout << "====================================================================================================================" << endl;
    cout << "1 - Enigma configuration (will reset your enigma machine)" << endl;
    cout << "2 - Encrypt text" << endl;
    cout << "3 - Encrypt characters showing steps" << endl;
    cout << "4 - Exit" << endl;
    cout << "====================================================================================================================" << endl;
}

void textEncryption(Enigma &en) {
    string input, output;
    cout << "Enter text to encrypt: ";
    getline(cin, input);
    output = en.encodeText(input);
    cout << output << endl;
    pause();
}

void encryptionSteps(Enigma &en) {
    while(true) {
        cout << "====================================================================================================================" << endl;
        printPositions(en);
        cout << "Type a letter to encrypt: ";

        string letter;
        getline(cin, letter);

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

int selectOption(Enigma &en, EnigmaConfig &config) {
    int option = -1;
    string input;
    cout << "Select option: ";
    getline(cin, input);

    if(input == "exit") {return 4;}

    try {
        option = stoi(input);
    } catch (const exception& e) {
    }

    switch (option) {
        case 1:
            handleConfiguration(en, config);
            break;
        case 2:
            textEncryption(en);
            break;
        case 3:
            encryptionSteps(en);
            break;
        case 4:
            cout << "exiting..." << endl;
            break;
        default:
            cout << "Wrong option: '" << input << "' is not a valid option." << endl;
            pause();
    }

    return option;
}

void interactiveMode() {
    EnigmaConfig config;
    Enigma en(config);

    while(true) {
        displayLogo();
        displayMenu();
        int option = selectOption(en, config);

        if(option == 4) {break;}
    }
}