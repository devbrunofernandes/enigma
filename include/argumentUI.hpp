#ifndef ARGUMENT_UI_HPP
#define ARGUMENT_UI_HPP

#include "enigma.hpp"
#include <iostream>
#include <vector>
#include <string>

void processStream(Enigma &en, std::istream &inStream, std::ostream &outStream);
void argumentMode(int argc, char* argv[], bool stdinIsTty);
std::vector<std::string> parseRotors(std::string rotors);

#endif