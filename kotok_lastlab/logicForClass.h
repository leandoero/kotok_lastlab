#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <raylib.h>
using namespace std;

class Tree {
private:
    struct Node {
        string text;
        Node* right;
        Node* left;

        Node(string inputText) {
            text = inputText;
            right = left = nullptr;
        }
    };

    vector<string>vectorForWords;
    Node* root;

    void print(Node* root);
    void clear(Node* root);
    int getDepth(Node* node);

    int numberWords(char inputLetter, Node* rootForFunc, int& count);

public:
    
    Tree() : root(nullptr) {}

    vector<string>& getVector() {
        return vectorForWords;
    }

    void addElFromFile(ifstream& file);
    
    int countFunc(char input);

    void addEl(string text);

    void print() {
        print(root);
    }

    ~Tree() {
        clear(root);
    }

    double timeTree(char letter);

    friend class raylibForProject;
};