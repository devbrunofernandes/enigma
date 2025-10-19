#ifndef ROTOR_HPP
#define ROTOR_HPP

#include <cctype>
#include <string>

using namespace std;

class Rotor {
private:
    string entryWiring;
    string reverseWiring;
    int position;
    char notch;

public:
    Rotor(string wiring, char notch, int startingPosition);
    bool rotate();
    char passLetter(char letter);
    char passLetterReverse(char letter);
    bool inNotch();
    int getPosition();
};

#endif