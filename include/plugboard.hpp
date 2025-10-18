#ifndef PLUGBOARD_HPP
#define PLUGBOARD_HPP

#include <cctype>
#include <stack>
#include <string>
#include <utility>
#include <algorithm>
#include <exception>
#include <sstream>

using namespace std;

#define MAX_CONNECTIONS 10

class Plugboard {
private:
    char letters[26];
    int connections;
    stack<pair<char, char>> lastConnections;

    void validateConnection(char x, char y) const;

public:
    Plugboard();
    Plugboard(string pairs);
    void connect(char x, char y);
    void reset();
    void undoConnection();
    void swap(char &x) const;
};

#endif