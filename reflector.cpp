#include "reflector.hpp"
#include <stdexcept>

Reflector::Reflector(std::string wiring) {
    transform(wiring.begin(), wiring.end(), wiring.begin(), ::tolower);

    validateWiring(wiring);

    this->wiring = wiring;
}

char Reflector::reflect(char input) const {
    if(!isalpha(input)) return input;

    return wiring[tolower(input) - 'a'];
}

void Reflector::validateWiring(const std::string wiring) {
    if(wiring.size() != 26) {
        throw std::invalid_argument("Invalid reflector configuration: '" + wiring + "' not cover exactly 26 alphabet letters.");
    }
}