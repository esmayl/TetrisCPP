#pragma once

enum BlockTypes
{
	Square,
	LShape,
	Line,
	ZShape,
};

struct Vector2 
{
	int x, y;
};

class Block
{
public:
	Block(int x, int y, int r, int g, int b, int a, BlockTypes blockType);
	void MoveDown(int fallStep);
	void MoveHorizontal(int direction);
	Vector2 pos;
	int r, g, b, a;
	Vector2 shape[4];
};