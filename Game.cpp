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

void Game::SetGridBlock(Vector2 pos,const Vector2* shape)
{
    int x;
    int y;
    
    for(int i =0;i<4;i++)
    {
        x = shape[i].x;
        y = shape[i].y;
        
        grid[pos.x+x][pos.y+y] = 1;
    }
    
    // std::cout << "Size: " << grid[0].size() << std::endl;
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

bool Game::CheckIfFullRow(int y)
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
