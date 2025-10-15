#include "enigma.hpp"
#include <iostream>
#include <vector>

using namespace std;

void printPositions(Enigma en) {
    vector<char> positions = en.rotorsPositions();
    for(char c: positions) {
        cout << c << " ";
    }
    cout << endl;
}

int main() {
    Enigma e;
    char c;

    while(true) {
        cout << "Current position of rotors: ";
        printPositions(e);
        cout << "Enter letter to encode: ";
        cin >> c;
        cout << "output: " << e.press(c) << endl;
    }

    // TESTING ROTORS
    // Rotor I("EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q', 1);
    // Rotor II("AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E', 1);
    // Rotor III("BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V', 1);
    // vector<Rotor> rotors = {I,II,III};

    // while (true) {
    //     int rotorIndex;
    //     cout << "Select a rotor to use (1 - 2 - 3): ";
    //     cin >> rotorIndex;
    //     rotorIndex--;
    //     rotors[rotorIndex].rotate();
    //     cout << "Enter letter to encode: ";
    //     cin >> c;
    //     cout << "output: " << rotors[rotorIndex].passLetter(c) << endl;
    // }

    return 0;
}