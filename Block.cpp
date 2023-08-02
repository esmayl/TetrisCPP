#include "Block.h"

Block::Block(int x, int y,int r,int g,int b,int a, BlockTypes blockType)
{
	this->pos.x = x;
	this->pos.y = y;

	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	this->canMove = true;

	switch (blockType)
	{
		case BlockTypes::Square:
			shape[0] = Vector2();
			shape[0].x = 0;
			shape[0].y = 0;

			shape[1] = Vector2();
			shape[1].x = 1;
			shape[1].y = 0;

			shape[2] = Vector2();
			shape[2].x = 1;
			shape[2].y = -1;

			shape[3] = Vector2();
			shape[3].x = 0;
			shape[3].y = -1;
			break;
		case BlockTypes::Line:
			shape[0] = Vector2();
			shape[0].x = 0;
			shape[0].y = 0;
			
			shape[1] = Vector2();
			shape[1].x = 0;
			shape[1].y = -1;

			shape[2] = Vector2();
			shape[2].x = 0;
			shape[2].y = -2;

			shape[3] = Vector2();
			shape[3].x = 0;
			shape[3].y = -3;
			break;
		case BlockTypes::LShape:
			shape[0] = Vector2();
			shape[0].x = 0;
			shape[0].y = 0;
				
			shape[1] = Vector2();
			shape[1].x = 1;
			shape[1].y = 0;

			shape[2] = Vector2();
			shape[2].x = 0;
			shape[2].y = -1;

			shape[3] = Vector2();
			shape[3].x = 0;
			shape[3].y = -2;
			break;
		case BlockTypes::ZShape:
			shape[0] = Vector2();
			shape[0].x = -1;
			shape[0].y = -1;
					
			shape[1] = Vector2();
			shape[1].x = 0;
			shape[1].y = -1;

			shape[2] = Vector2();
			shape[2].x = 0;
			shape[2].y = 0;

			shape[3] = Vector2();
			shape[3].x = 1;
			shape[3].y = 0;
			break;
	}
}

void Block::Move(int fallStep, int direction)
{
	pos.x += direction;
	pos.y += fallStep;
}
