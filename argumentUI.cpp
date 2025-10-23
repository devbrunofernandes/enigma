#include "argumentUI.hpp"
#include <sstream>
#include <string>

void processStream(Enigma &en, std::istream &inStream, std::ostream &outStream) {
    std::stringstream buffer;
    buffer << inStream.rdbuf();
    std::string input = buffer.str();
    std::string output = en.encodeText(input);
    outStream << output;
}