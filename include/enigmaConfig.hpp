#include <vector>
#include <string>

struct EnigmaConfig {
    std::vector<std::string> rotorNames = {"I", "II", "III"};
    std::string rotorInitial = "AAA";
    std::string plugboardConnections = "";
    std::string reflector = "B";
};