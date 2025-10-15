#include "enigma.hpp"
#include "plugboard.hpp"
#include "reflector.hpp"

#include <iostream>

using namespace std;

// default values for reflectors
#define REFLECTOR_A Reflector("EJMZALYXVBWFCRQUONTSPIKHGD")
#define REFLECTOR_B Reflector("YRUHQSLDPXNGOKMIEBFZCWVJAT")
#define REFLECTOR_C Reflector("FVPJIAOYEDRZXWGCTKUQSBNMHL")

// default values for rotors
#define ROTOR_I Rotor("EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q', 1)
#define ROTOR_II Rotor("AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E', 1)
#define ROTOR_III Rotor("BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V', 1)
#define ROTOR_IV Rotor("ESOVPZJAYQUIRHXLNFTGKDCMWB", 'J', 1)
#define ROTOR_V Rotor("VZBRGITYUPSDNHLXAWMJQOFECK", 'Z', 1)

/*  Default Enigma constructor:
    Rotors: I II III
    Rotors starting position: 1 1 1
    Reflector: B
    No plugboard change
*/
Enigma::Enigma() : r("YRUHQSLDPXNGOKMIEBFZCWVJAT"), pb() {
    rotors.push_back(ROTOR_I);
    rotors.push_back(ROTOR_II);
    rotors.push_back(ROTOR_III);
}

char Enigma::rotorsTraverse(char letter, int current_rotor) {
    // if(current_rotor < 0)
    //     return r.reflect(letter);

    // letter = rotors[current_rotor].passLetter(letter);
    // letter = rotorsTraverse(letter, current_rotor-1);
    // letter = rotors[current_rotor].passLetter(letter);

    cout << "=======================================" << endl;
    for(int i = current_rotor; i >= 0; i--) {
        letter = rotors[i].passLetter(letter);
        cout << "current letter: " << letter << endl;
    }
        

    letter = r.reflect(letter);
    cout << "reflects into: " << letter << endl;

    for(int i = 0; i < rotors.size(); i++) {
        letter = rotors[i].passLetterReverse(letter);
        cout << "current letter: " << letter << endl;
    }
    cout << "=======================================" << endl;

    return letter;
}

char Enigma::encode(char input) {
    char output = input;

    pb.swap(output);
    output = rotorsTraverse(output, rotors.size()-1);
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

vector<char> Enigma::rotorsPositions() {
    vector<char> positions;
    for(Rotor ro: rotors) {
        positions.push_back(ro.getPosition() + 'a');
    }
    return positions;
}