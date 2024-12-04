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
    raylibForProject* tree = new raylibForProject();
    
    tree->addElFromFile(inputFile);
    
    tree->Window();
    CloseWindow();
    delete tree;
    inputFile.close();
    return 0;
}
