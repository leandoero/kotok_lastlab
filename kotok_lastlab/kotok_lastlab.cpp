#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <raylib.h>

using namespace std;

class Tree {
    struct Node {
        string text;
        Node* right;
        Node* left;

        Node(string inputText) {
            text = inputText;
            right = left = nullptr;
        }
    };

    Node* root;

    void print(Node* root) {
        if (root == nullptr) {
            return;
        }
        print(root->left);
        cout << root->text << endl;
        print(root->right);
    }

    void clear(Node* root) {
        if (root == nullptr) {
            return;
        }
        clear(root->left);
        clear(root->right);
        delete root;
    }

    int getDepth(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + max(getDepth(node->left), getDepth(node->right));
    }

    void drawTree(Vector2 position, Node* node, float offsetX, char letter) {
        if (node != nullptr) {
            if (node->text[0] == letter) DrawCircleV(position, 20, RED);
            else DrawCircleV(position, 20, BLUE);

            DrawText(node->text.c_str(), position.x - MeasureText(node->text.c_str(), 10) / 2, position.y - 10, 10, WHITE);

            if (node->left != nullptr) {
                Vector2 leftPos = { position.x - offsetX, position.y + 60 };
                DrawLineV(position, leftPos, DARKGRAY);              
                drawTree(leftPos, node->left, offsetX / 2, letter);
            }

            if (node->right != nullptr) {
                Vector2 rightPos = { position.x + offsetX, position.y + 60 };
                DrawLineV(position, rightPos, DARKGRAY);
                drawTree(rightPos, node->right, offsetX / 2, letter);
            }
        }
    }
    int numberWords(char inputLetter, Node* rootForFunc, int& count) {
        if (rootForFunc == nullptr) {
            return -1;
        }
        numberWords(inputLetter, rootForFunc->left, count);
        if (inputLetter == rootForFunc->text[0]) {
            ++count;

        }
        numberWords(inputLetter, rootForFunc->right, count);
        return count;
    }

public:
    Tree() : root(nullptr) {}

    int countFunc(char input) {
        int count = 0;
        count = numberWords(input, root, count);
        return count;

    }
    void addEl(string text) {
        Node* cur = root;
        Node* parent = nullptr;
        if (root == nullptr) {
            root = new Node(text);
            return;
        }
        while (cur != nullptr) {
            parent = cur;
            if (text < cur->text) {
                cur = cur->left;
            }
            else if (text > cur->text) {
                cur = cur->right;
            }
            else {
                return;
            }
        }
        if (text < parent->text) {
            parent->left = new Node(text);
        }
        else {
            parent->right = new Node(text);
        }
    }

    vector<string> vectorForWords;

    void print() {
        print(root);
    }

    ~Tree() {
        clear(root);
    }

    double countFile(char letter, vector<string>& words) {
        int count = 0;
        for (string word : words) {
            if (letter == word[0]) {
                count++;
            }
        }
        return count;
    }

    double timeFile(char letter, vector<string>& words) {
        auto start = std::chrono::high_resolution_clock::now();
        countFile(letter, words);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        return duration.count();
    }
    double timeTree(char letter) {
        auto start = std::chrono::high_resolution_clock::now();
        countFunc(letter);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        return duration.count();
    }

    void Window(Tree*& tree) {
        const int screenHeight = 800;
        const int screenWidth = 800;
        InitWindow(screenHeight,screenWidth, "Tree");
        SetTargetFPS(60);
        int depth = getDepth(root);
        float initialOffset = std::max(200.0, 800.0 / (pow(2, depth - 1) * 2));

        while (!WindowShouldClose()) {
            static char currentLetter = '\0';  
            int key = GetCharPressed();
            if (key != 0 && isprint(key)) {  
                currentLetter = (char)key;  
            }
            bool letterReady = false;
            BeginDrawing();
            ClearBackground(RAYWHITE);

            drawTree({ 400, 50 }, root, initialOffset, currentLetter);
            DrawRectangle(0, screenHeight - 200, screenWidth, 100, DARKGRAY);
            DrawRectangle(0, screenHeight - 100, screenWidth, 100, LIGHTGRAY);
            
            DrawText("Enter letter: ", 10, screenHeight - 90, 20, DARKGRAY);

            if (currentLetter != '\0') {
                char displayText[50];
                char treeText[50];
                char fileText[50];
                double timeForTree = timeTree(currentLetter);
                double timeForFile = timeFile(currentLetter, vectorForWords);
                snprintf(displayText, sizeof(displayText), "Input: %c", currentLetter);
                snprintf(treeText, sizeof(treeText), "Tree search time: %f", timeForTree);
                snprintf(fileText, sizeof(fileText), "File search time: %f", timeForFile);
                DrawText(displayText, 10, screenHeight - 60, 20, DARKGRAY);
                DrawText(treeText, 10, screenHeight - 180, 20, LIGHTGRAY);
                DrawText(fileText, 10, screenHeight - 140, 20, LIGHTGRAY);
            }
            char numberText[30];
            if (currentLetter != '\0') {
                letterReady = true;
                if (letterReady) {
                    int count = tree->countFunc(currentLetter);
                    snprintf(numberText, sizeof(numberText), "Number of elements: %d", count);
                    letterReady = false;
                }
            }
            DrawText(numberText, 10, 10, 20, DARKGRAY);
            EndDrawing();
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    ifstream inputFile("words.txt");
    if (!inputFile) {
        cout << "Error" << endl;
        return -1;
    }
    Tree* tree = new Tree();
    
    string line;
    while (getline(inputFile, line)) {
        tree->vectorForWords.push_back(line);
    }

    

    for (int i = 0; i < tree->vectorForWords.size(); i++)
    {
        tree->addEl(tree->vectorForWords[i]);
    }


    tree->Window(tree);
    CloseWindow();
    delete tree;
    inputFile.close();
    return 0;
}
