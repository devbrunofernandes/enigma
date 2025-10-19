#ifndef INTERACTIVE_UI_HPP
#define INTERACTIVE_UI_HPP

#include "enigma.hpp"

void displayLogo(int terminalWidth);
void displayMenu(int terminalWidth);
int selectOption(Enigma &en, EnigmaConfig &config, int terminalWidth);
void interactiveMode();
void printPositions(Enigma en);
void textEncryption(Enigma &en);
void encryptionSteps(Enigma &en);
void waitForEnter();
int getTerminalWidth();

// configuration functions
void handleConfiguration(Enigma &en, EnigmaConfig &config, int terminalWidth);
void configurationMenu(int terminalWidth);
int selectConfigurationOption(Enigma &en, EnigmaConfig &config);
void rotorConfiguration(EnigmaConfig &config);
void rotorPositionConfiguration(EnigmaConfig &config);
void plugboardConfiguration(EnigmaConfig &config);
void reflectorConfiguration(EnigmaConfig &config);
void showConfiguration(EnigmaConfig &config);

#endif