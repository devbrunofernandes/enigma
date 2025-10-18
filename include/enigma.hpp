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
    char encode(char input);
    char rotorsTraverse(char letter);
    void generateRotors(const EnigmaConfig config);

public:
    Enigma();
    char press(char pressed_key);
    vector<char> getRotorsPositions() const;
};

#endif