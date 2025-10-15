#ifndef REFLECTOR_HPP
#define REFLECTOR_HPP

#include <string>
#include <algorithm>

class Reflector {
private:
    std::string wiring;

    void validateWiring(const std::string wiring);

public:
    Reflector(std::string wiring);
    char reflect(char input) const;
};

#endif