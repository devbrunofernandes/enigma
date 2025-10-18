#include "enigma.hpp"
#include "plugboard.hpp"
#include "reflector.hpp"
#include <stdexcept>

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

char Enigma::rotorsTraverse(char letter) {
    for(int i = rotors.size() - 1; i >= 0; i--) {
        letter = rotors[i].passLetter(letter);
    }
    letter = r.reflect(letter);
    for(int i = 0; i < rotors.size(); i++) {
        letter = rotors[i].passLetterReverse(letter);
    }

    return letter;
}

char Enigma::encode(char input) {
    char output = input;

    pb.swap(output);
    output = rotorsTraverse(output);
    pb.swap(output);

    return output;
}

void Enigma::rotorsRotate() {
    int currentRotor = rotors.size()-1;

    while(currentRotor >= 0 && (rotors[currentRotor].rotate() || (currentRotor > 0 && rotors[currentRotor-1].inNotch()))) {
        currentRotor--;
    }
}

char Enigma::press(char pressed_key) {
    pressed_key = tolower(pressed_key);

    rotorsRotate();

    if(!isalpha(pressed_key)) return pressed_key;

    return encode(pressed_key);
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
            tmpRotors.push_back(Rotor(ROTOR_I, config.rotorInitial[positionIndex] - 'a'));
        } else if(s == "II") {
            tmpRotors.push_back(Rotor(ROTOR_II, config.rotorInitial[positionIndex] - 'a'));
        } else if(s == "III") {
            tmpRotors.push_back(Rotor(ROTOR_III, config.rotorInitial[positionIndex] - 'a'));
        } else if(s == "IV") {
            tmpRotors.push_back(Rotor(ROTOR_IV, config.rotorInitial[positionIndex] - 'a'));
        } else if(s == "V") {
            tmpRotors.push_back(Rotor(ROTOR_V, config.rotorInitial[positionIndex] - 'a'));
        } else {
            throw invalid_argument("Invalid rotor configuration: '" + s + "' is not a type of rotor.");
        }
        positionIndex++;
    }

    rotors = tmpRotors;
}