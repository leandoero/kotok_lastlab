#pragma once
#include "logicForClass.h"
#include "logicForOther.h"
#include <raylib.h>

class raylibForProject {
public:
	void drawTree(Vector2 position, Tree::Node* tree, float offsetX, char letter);
	void Window(Tree*& tree);
};
