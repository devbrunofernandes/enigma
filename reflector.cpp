#include "reflector.hpp"

Reflector::Reflector(std::string wiring) {
    transform(wiring.begin(), wiring.end(), wiring.begin(), ::tolower);
    this->wiring = wiring;
}

char Reflector::reflect(char input) {
    if(!isalpha(input)) return input;

    return wiring[tolower(input) - 'a'];
}