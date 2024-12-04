#pragma once
#include "logicForClass.h"
#include "logicForOther.h"
#include <raylib.h>

class raylibForProject : public Tree{
public:
	void drawTree(Vector2 position, Node* node, float offsetX, char letter);
	void Window();
};
