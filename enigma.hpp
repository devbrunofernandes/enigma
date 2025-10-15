#ifndef ENIGMA_HPP
#define ENIGMA_HPP

#include "plugboard.hpp"
#include "rotor.hpp"
#include "reflector.hpp"
#include <vector>

using namespace std;

#define MIN_ROTORS 3

class Enigma {
private:
    vector<Rotor> rotors;
    Reflector r;
    Plugboard pb;

public:
    Enigma();
    char press(char pressed_key);
    char encode(char input);
    char rotorsTraverse(char letter, int current_rotor); 
    void rotorsRotate();
    vector<char> rotorsPositions();
};

#endif