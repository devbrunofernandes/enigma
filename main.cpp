#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "doublyLinkedList.hpp"

using namespace std;

string getFilePath() {
    string filePath = "";

    while(filePath.find(".txt") == -1) {
        cout << "Enter text file path: ";
        cin >> filePath;
    }

    return filePath;
}

DoublyLinkedList *initializeLettersList() {
    DoublyLinkedList *letters = new DoublyLinkedList;
    int index = 0;

    for(char i='a'; i<='z'; i++) {
        letters->insert(index, i);
        index++;
    }

    return letters;
}

void getSingleLetterChange(DoublyLinkedList *lettersList, char *lettersArray, int listSize) {
    Node *p = lettersList->head;
    srand(time(0)); // seed random number based on time
    int firstLetter, secondLetter, position, i;
    firstLetter = lettersList->remove(1);
    position = (random() % (listSize - 1)) + 1;

    for(i=1; i<=position; i++) {
        p=p->next;
    }

    secondLetter = lettersList->remove(i);
    lettersArray[firstLetter - 'a'] = secondLetter;
    lettersArray[secondLetter - 'a'] = firstLetter;
}

char* changeLetters() {
    char *lettersArray = new char[26];
    DoublyLinkedList *lettersList = initializeLettersList();
    int listSize = 26;

    while(!lettersList->empty()) {
        getSingleLetterChange(lettersList, lettersArray, listSize);
        listSize -= 2;
    }

    delete lettersList;
    return lettersArray;
}

// TODO
char encryptChar(char c) {
    char result;

    if(not isalpha(c)) {
        return c;
    }

    return result;
}

string encryptMessage(ifstream file) {
    string message = "";
    char c;

    while(not file.eof()) {
        c = file.get();
        message += encryptChar(c);
    }

    return message;
}

int main() {
    string filePath = getFilePath();

    ifstream text;

    text.open(filePath);

    char *changedLetters = changeLetters();
    string encrypt = encryptMessage(text);

    delete changedLetters;
    text.close();

    return 0;
}