#include <iostream>
#include <fstream>
#include <vector>
#include <raylib.h>
#include "logicForClass.h";
#include "raylibLib.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    ifstream inputFile("words.txt");
    if (!inputFile) {
        cout << "Error" << endl;
        return -1;
    }
    Tree* tree = new Tree();
    raylibForProject* project = new raylibForProject();
    tree->addElFromFile(inputFile);
    
    project->Window(tree);

    delete tree;
    delete project;

    inputFile.close();
    return 0;
}
