#include "rotor.hpp"

using namespace std;

Rotor::Rotor(string wiring, char notch, int startingPosition) {
    transform(wiring.begin(), wiring.end(), wiring.begin(), ::tolower);
    notch = tolower(notch);

    entryWiring = wiring;
    this->notch = notch;
    position = startingPosition - 1;
}

bool Rotor::rotate() {
    bool turnover = (position + 'a') == notch;

    position = (position + 1) % 26;

    return turnover;
}

char Rotor::passLetter(char letter) {
    if(!isalpha(letter)) return letter;
    letter = tolower(letter);
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char internalChange = entryWiring[(letter - 'a' + position) % 26];
    internalChange = internalChange - 'a' - position < 0 ? alphabet[internalChange - 'a' - position + 26] : alphabet[internalChange - 'a' - position];
    return internalChange;
}