#include "reflector.hpp"

Reflector::Reflector(std::string wiring) {
    if(wiring.size() != 26) throw std::exception();
    transform(wiring.begin(), wiring.end(), wiring.begin(), ::tolower);
    this->wiring = wiring;
}

char Reflector::reflect(char input) {
    if(!isalpha(input)) return input;

    return wiring[tolower(input) - 'a'];
}