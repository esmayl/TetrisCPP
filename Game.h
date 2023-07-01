#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "Block.h"

class Game
{
    public:
        Game(int width, int height);
        void SetGridBlock(Vector2 pos,const Vector2* shape);
        void RemoveGridBlock(int x, int y);
        bool CheckIfFullRow(int y);
        bool CheckIfReachedEnd(Vector2 pos,Vector2* shape);

    private:
        std::vector<std::vector<int>> grid;
};
