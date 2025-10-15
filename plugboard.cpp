#include "plugboard.hpp"

Plugboard::Plugboard() {
    for(char i='a'; i<='z'; i++) {
        letters[i - 'a'] = i;
    }
    connections = 0;
}

void Plugboard::connect(char x, char y) {
    x = tolower(x);
    y = tolower(y);

    if(x == y) return;
    if(connections == MAX_CONNECTIONS) return;
    // check for outbound
    if(!isalpha(x) || !isalpha(y)) return;
    // check for already connected letters
    if(letters[x - 'a'] != x || letters[y - 'a'] != y) return;

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