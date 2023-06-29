#pragma once
class Block
{
public:
	Block(int x, int y, int r, int g, int b, int a);
	void MoveDown(int fallStep);
	void MoveHorizontal(int direction);
	int x, y;
	int r, g, b, a;
};

