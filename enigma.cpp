#include "enigma.hpp"
#include <cctype>
#include <stdexcept>
#include <iostream>

using namespace std;

// default values for reflectors
#define REFLECTOR_A "EJMZALYXVBWFCRQUONTSPIKHGD"
#define REFLECTOR_B "YRUHQSLDPXNGOKMIEBFZCWVJAT"
#define REFLECTOR_C "FVPJIAOYEDRZXWGCTKUQSBNMHL"

// default values for rotors
#define ROTOR_I "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q'
#define ROTOR_II "AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E'
#define ROTOR_III "BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V'
#define ROTOR_IV "ESOVPZJAYQUIRHXLNFTGKDCMWB", 'J'
#define ROTOR_V "VZBRGITYUPSDNHLXAWMJQOFECK", 'Z'

/*  Default Enigma constructor:
    Rotors: I II III
    Rotors starting position: 1 1 1
    Reflector: B
    No plugboard change
*/
Enigma::Enigma() : r(REFLECTOR_B), pb() {
    rotors.push_back(Rotor(ROTOR_I, 0));
    rotors.push_back(Rotor(ROTOR_II, 0));
    rotors.push_back(Rotor(ROTOR_III, 0));
}

Enigma::Enigma(EnigmaConfig config) : r(chooseReflector(config.reflector)), pb(config.plugboardConnections) {
    generateRotors(config);
}

char Enigma::rotorsTraverse(char letter, bool showSteps) {
    char lastLetter = letter;

    for(int i = rotors.size() - 1; i >= 0; i--) {
        letter = rotors[i].passLetter(letter);
        if(showSteps) {
            cout << i+1 << "nd Rotor: " << lastLetter << " -> " << letter << endl;
            lastLetter = letter;
        }
    }

    letter = r.reflect(letter);
    if(showSteps) {
        cout << "Reflector: " << lastLetter << " -> " << letter << endl;
        lastLetter = letter;
    }

    for(int i = 0; i < rotors.size(); i++) {
        letter = rotors[i].passLetterReverse(letter);
        if(showSteps) {
            cout << i+1 << "nd Rotor: " << lastLetter << " -> " << letter << endl;
            lastLetter = letter;
        }
    }

    return letter;
}

char Enigma::encode(char input, bool showSteps) {
    char output = input, lastLetter = output;

    pb.swap(output);
    if(showSteps) {
        cout << "Plugboard: " << lastLetter << " -> " << output << endl;
        lastLetter = output;
    }
    output = rotorsTraverse(output, showSteps);
    pb.swap(output);
    if(showSteps) {
        cout << "Plugboard: " << lastLetter << " -> " << output << endl;
        lastLetter = output;
    }

    return output;
}

void Enigma::rotorsRotate() {
    int currentRotor = rotors.size()-1;

    while(currentRotor >= 0 && (rotors[currentRotor].rotate() || (currentRotor > 0 && rotors[currentRotor-1].inNotch()))) {
        currentRotor--;
    }
}

char Enigma::press(char pressed_key, bool showSteps) {
    pressed_key = tolower(pressed_key);

    rotorsRotate();

    if(!isalpha(pressed_key)) return pressed_key;

    return encode(pressed_key, showSteps);
}

vector<char> Enigma::getRotorsPositions() const {
    vector<char> positions;
    for(Rotor ro: rotors) {
        positions.push_back(ro.getPosition() + 'a');
    }
    return positions;
}

void Enigma::generateRotors(const EnigmaConfig config) {
    vector<Rotor> tmpRotors;
    int positionIndex = 0;

    if(config.rotorInitial.size() != config.rotorNames.size()) {
        throw invalid_argument("Invalid configuration: rotors names and initial positions doesn't match.");
    }

    for(string s: config.rotorNames) {
        if(s == "I") {
            tmpRotors.push_back(Rotor(ROTOR_I, toupper(config.rotorInitial[positionIndex]) - 'A'));
        } else if(s == "II") {
            tmpRotors.push_back(Rotor(ROTOR_II, toupper(config.rotorInitial[positionIndex]) - 'A'));
        } else if(s == "III") {
            tmpRotors.push_back(Rotor(ROTOR_III, toupper(config.rotorInitial[positionIndex]) - 'A'));
        } else if(s == "IV") {
            tmpRotors.push_back(Rotor(ROTOR_IV, toupper(config.rotorInitial[positionIndex]) - 'A'));
        } else if(s == "V") {
            tmpRotors.push_back(Rotor(ROTOR_V, toupper(config.rotorInitial[positionIndex]) - 'A'));
        } else {
            throw invalid_argument("Invalid rotor configuration: '" + s + "' is not a type of rotor.");
        }
        positionIndex++;
    }

    rotors = tmpRotors;
}

string Enigma::chooseReflector(string reflectorName) {
    string reflectorConnections;
    transform(reflectorName.begin(), reflectorName.end(), reflectorName.begin(), ::toupper);

    if(reflectorName == "A") {
        reflectorConnections = REFLECTOR_A;
    } else if(reflectorName == "B") {
        reflectorConnections = REFLECTOR_B;
    } else if(reflectorName == "C") {
        reflectorConnections = REFLECTOR_C;
    } else {
        throw invalid_argument("Invalid reflector configuration: '" + reflectorName + "' is not a type of reflector.");
    }

    return reflectorConnections;
}

string Enigma::encodeText(string text) {
    string output = "";

    for(char c: text) {
        if(isalpha(c)) {
            output += press(c, false);
        } else {
            output += c;
        }
    }

    return output;
}   