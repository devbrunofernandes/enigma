#include "rotor.hpp"
#include <algorithm>
#include <exception>
#include <stdexcept>

using namespace std;

Rotor::Rotor(string wiring, char notch, int startingPosition) {
    if(wiring.size() != 26) throw exception();

    transform(wiring.begin(), wiring.end(), wiring.begin(), ::tolower);
    notch = tolower(notch);

    entryWiring = wiring;
    reverse(wiring.begin(), wiring.end());
    reverseWiring = wiring;
    this->notch = notch;
    position = startingPosition;
}

bool Rotor::rotate() {
    bool turnover = position == notch - 'a';

    position = (position + 1) % 26;

    return turnover;
}

char Rotor::passLetter(char letter) {
    if(!isalpha(letter)) return letter;
    letter = tolower(letter);
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    // DEBUGGING
    int index =  (letter - 'a' + position) % 26;
    if(index >= 26 || index < 0) throw out_of_range("Index of letter change out of range");

    char internalChange = entryWiring[index];
    internalChange = internalChange - 'a' - position < 0 ? alphabet[internalChange - 'a' - position + 26] : alphabet[internalChange - 'a' - position];
    
    return internalChange;
}

char Rotor::passLetterReverse(char letter) {
    if(!isalpha(letter)) return letter;
    letter = tolower(letter);
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    int index = (alphabet[(letter - 'a')] - 'a' + position) % 26;

    int outputPosition;
    for(outputPosition=0; outputPosition<26; outputPosition++)
        if(entryWiring[outputPosition] == alphabet[index]) break;

    outputPosition = outputPosition - position < 0 ? outputPosition - position + 26 : outputPosition - position;

    return alphabet[outputPosition];
}

bool Rotor::inNotch() {
    return position == notch - 'a';
}

int Rotor::getPosition() {
    return position;
}