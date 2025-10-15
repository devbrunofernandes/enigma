#include "plugboard.hpp"
#include <stdexcept>

Plugboard::Plugboard() {
    for(char i='a'; i<='z'; i++) {
        letters[i - 'a'] = i;
    }
    connections = 0;
}

Plugboard::Plugboard(string pairs) {
    for(char i='a'; i<='z'; i++) {
        letters[i - 'a'] = i;
    }
    connections = 0;

    transform(pairs.begin(), pairs.end(), pairs.begin(), ::tolower);

    stringstream ss(pairs);
    string currentPair;

    while(ss >> currentPair) {
        if(currentPair.length() != 2) {throw invalid_argument("Invalid plugboard configuration: '" + currentPair + "' is not a valid pair.");}

        char c1 = currentPair[0], c2 = currentPair[1];
        connect(c1, c2);
    }
}

void Plugboard::connect(char x, char y) {
    x = tolower(x);
    y = tolower(y);

    validateConnection(x, y);
    
    letters[x - 'a'] = y;
    letters[y - 'a'] = x;
    lastConnections.push({x, y});
    connections++;
}

void Plugboard::clear() {
    for(char i='a'; i<='z'; i++) {
        letters[i - 'a'] = i;
    }
    connections = 0;
    
    while(!lastConnections.empty()) lastConnections.pop();
}

void Plugboard::undoConnection() {
    if(lastConnections.empty()) return;

    pair<char,char> p = lastConnections.top();
    letters[p.first - 'a'] = p.first;
    letters[p.second - 'a'] = p.second;
    lastConnections.pop();
    connections--;
}

void Plugboard::swap(char &x) {
    if(isalpha(x)) {
        x = letters[x - 'a'];
    }
}

void Plugboard::validateConnection(char x, char y) {
    string currentPair = string(1, x) + string(1, y);
    if(!isalpha(x) || !isalpha(y)) {
        throw invalid_argument("Invalid plugboard configuration: '" + currentPair + "' has non-alphabetic characters.");
    }
    if(x == y) {
        throw invalid_argument("Invalid plugboard configuration: '" + currentPair + "' can not connect the same letter.");
    }
    if(letters[x-'a'] != x || letters[y-'a'] != y) {
        throw invalid_argument("Invalid plugboard configuration: '" + currentPair + "' already have connected letters.");
    }
}