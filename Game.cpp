#include "Game.h"

Game::Game(int width,int height)
{
    grid.resize(width);
    
    for (int i = 0; i < width; i++)
    {
        grid[i].resize(height);
        
        for (int j =0;j<height;j++)
        {
            grid[i][j] = 0;
        }
    }
}

void Game::SetGridBlock(Block* block, int cellSize, int direction)
{
    int newX;
    int newY;
    
    for(int i =0;i<4;i++)
    {
        newX = block->pos.x / cellSize + block->shape[i].x;
        newY = block->pos.y / cellSize + block->shape[i].y;

        if(newX >= 0 && newY >= 0)
        {
            if(newY > 0)
            {
                grid[newX-direction][newY-1] = 0;
            }
        }
    }

    for(int i =0;i<4;i++)
    {
        newX = block->pos.x / cellSize + block->shape[i].x;
        newY = block->pos.y / cellSize + block->shape[i].y;
        
        if(newX >= 0 && newY >= 0)
        {
            grid[newX][newY] = 1;
        }
    }
    
    // std::string str = "";
    //
    // for (int i = 0;i < grid[0].size();i++)
    // {
    //     for (int j =0; j < grid.size();j++)
    //     {
    //         str += std::to_string(grid[j][i]);
    //     }
    //     std::cout << str << std::endl;
    //     str = "";
    // }
    //
    // std::cout << std::endl;
    // std::cout << std::endl;
}

void Game::RemoveGridBlock(int x, int y)
{
}

bool Game::CheckIfFullRow(int y,Vector2* shape)
{
    return false;
}

bool Game::CheckIfReachedEnd(Vector2 pos,Vector2* shape)
{
    if(pos.y < grid[0].size()-1)
    {
        if(grid[pos.x][pos.y+1] == 1)
        {
            return true;
        }
    }
    else if(grid[pos.x][pos.y] == 1)
    {
        return true;
    }
    else
    {
        if(grid[0].size()-1 == pos.y)
        {
            return true;
        }   
    }
    

    return false;
}
