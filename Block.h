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

	Vector2()
	{
		x = 0;
		y = 0;
	}
	
	Vector2(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	
	Vector2 operator / (int i) const
	{
		return Vector2(x/i,y/i);
	}
};

class Block
{
public:
	Block(int x, int y, int r, int g, int b, int a, BlockTypes blockType);
	void Move(int fallStep, int direction);
	Vector2 pos;
	int r, g, b, a;
	Vector2 shape[4];
	bool canMove = true;
};