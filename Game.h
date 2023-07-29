#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "Block.h"

class Game
{
    public:
        Game(int width, int height);
        void SetGridBlock(Block* block, int cellSize, int direction);
        void RemoveGridBlock(int x, int y);
        bool CheckIfFullRow(int y,Vector2* shape);
        bool CheckIfReachedEnd(Vector2 pos,Vector2* shape);
    
        std::vector<std::vector<int>> grid;
};
