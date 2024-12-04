#include "raylibLib.h"


void raylibForProject::drawTree(Vector2 position, Tree::Node* root, float offsetX, char letter) {
    if (root != nullptr) {
        if (root->text[0] == letter) DrawCircleV(position, 20, RED);
        else DrawCircleV(position, 20, BLUE);

        DrawText(root->text.c_str(), position.x - MeasureText(root->text.c_str(), 10) / 2, position.y - 10, 10, WHITE);

        if (root->left != nullptr) {
            Vector2 leftPos = { position.x - offsetX, position.y + 60 };
            DrawLineV(position, leftPos, DARKGRAY);
            drawTree(leftPos, root->left, offsetX / 2, letter);
        }

        if (root->right != nullptr) {
            Vector2 rightPos = { position.x + offsetX, position.y + 60 };
            DrawLineV(position, rightPos, DARKGRAY);
            drawTree(rightPos, root->right, offsetX / 2, letter);
        }
    }
}
void raylibForProject::Window(Tree*& tree) {
    const int screenHeight = 800;
    const int screenWidth = 800;
    InitWindow(screenHeight, screenWidth, "Tree");
    SetTargetFPS(60);
    int depth = tree->getDepth(tree->root);
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

        drawTree({ 400, 50 }, tree->root, initialOffset, currentLetter);
        DrawRectangle(0, screenHeight - 200, screenWidth, 100, DARKGRAY);
        DrawRectangle(0, screenHeight - 100, screenWidth, 100, LIGHTGRAY);

        DrawText("Enter letter: ", 10, screenHeight - 90, 20, DARKGRAY);

        if (currentLetter != '\0') {
            char displayText[50];
            char treeText[50];
            char fileText[50];
            double timeForTree = tree->timeTree(currentLetter);
            double timeForFile = timeFile(currentLetter, tree->getVector());
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

    CloseWindow();
}