#ifndef ROTOR_HPP
#define ROTOR_HPP

#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

class Rotor {
private:
    string entryWiring;
    int position;
    char notch;

public:
    Rotor(string wiring, char notch, int startingPosition);
    bool rotate();
    char passLetter(char letter);
};

#endif