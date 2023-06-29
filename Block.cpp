#include "Block.h"

Block::Block(int x, int y,int r,int g,int b,int a)
{
	this->x = x;
	this->y = y;

	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Block::MoveDown(int fallStep)
{
	y += fallStep;
}

void Block::MoveHorizontal(int direction)
{
	x += direction;
}
