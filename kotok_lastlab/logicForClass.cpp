#include "logicForClass.h"

void Tree::print(Node* root) {
    if (root == nullptr) {
        return;
    }
    print(root->left);
    cout << root->text << endl;
    print(root->right);
}

void Tree::clear(Node* root) {
    if (root == nullptr) {
        return;
    }
    clear(root->left);
    clear(root->right);
    delete root;
}

int Tree::getDepth(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return 1 + max(getDepth(node->left), getDepth(node->right));
}

int Tree::numberWords(char inputLetter, Node* rootForFunc, int& count) {
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

int Tree::countFunc(char input) {
    int count = 0;
    count = numberWords(input, root, count);
    return count;

}
void Tree::addEl(string text) {
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
double Tree::timeTree(char letter) {
    auto start = std::chrono::high_resolution_clock::now();
    countFunc(letter);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return duration.count();
}

void Tree::addElFromFile(ifstream& file) {
    string line;
    while (getline(file, line)) {
        vectorForWords.push_back(line);
    }
    for (int i = 0; i < vectorForWords.size(); i++)
    {
        addEl(vectorForWords[i]);
    }
}