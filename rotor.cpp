
#include <cctype>
#include <string>

using namespace std;

class Rotor {
private:
    string entryWiring;
    int position;
    char notch;

public:
    Rotor(string wiring, char notch, int startingPosition) {
        entryWiring = wiring;
        this->notch = notch;
        position = startingPosition;
    }

    bool rotate() {
        bool turnover = entryWiring[position] == notch;

        position = (position + 1) % 25;

        return turnover;
    }

    char passLetter(char letter) {
        if(!isalpha(letter)) return letter;

        return entryWiring[(letter - 'a' + position) % 25];
    }
};

int main() {
    return 0;
}