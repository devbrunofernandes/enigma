#ifndef INTERACTIVE_UI_HPP
#define INTERACTIVE_UI_HPP

#include "enigma.hpp"

void displayLogo();
void displayMenu();
int selectOption(Enigma &en, EnigmaConfig &config);
void interactiveMode();
void printPositions(Enigma en);
void textEncryption(Enigma &en);
void encryptionSteps(Enigma &en);
void pause();

// configuration functions
void handleConfiguration(Enigma &en, EnigmaConfig &config);
void configurationMenu();
int selectConfigurationOption(Enigma &en, EnigmaConfig &config);
void rotorConfiguration(EnigmaConfig &config);
void rotorPositionConfiguration(EnigmaConfig &config);
void plugboardConfiguration(EnigmaConfig &config);
void reflectorConfiguration(EnigmaConfig &config);
void showConfiguration(EnigmaConfig &config);

#endif