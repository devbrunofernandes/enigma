#ifndef ENIGMA_HPP
#define ENIGMA_HPP

#include "plugboard.hpp"
#include "rotor.hpp"
#include "reflector.hpp"
#include "enigmaConfig.hpp"
#include <vector>

using namespace std;

#define MIN_ROTORS 3

class Enigma {
private:
    vector<Rotor> rotors;
    Reflector r;
    Plugboard pb;

    void rotorsRotate();
    char encode(char input, bool showSteps);
    char rotorsTraverse(char letter, bool showSteps);
    void generateRotors(const EnigmaConfig config);
    string chooseReflector(string reflectorName);

public:
    Enigma();
    Enigma(EnigmaConfig config);
    char press(char pressed_key, bool showSteps);
    vector<char> getRotorsPositions() const;
    string encodeText(string text);
};

#endif