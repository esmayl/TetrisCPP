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

        if(newX >= 0 && newY >= 0 && newY < grid[0].size() && newX < grid.size())
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
        
        if(newX >= 0 && newY >= 0 && newY < grid[0].size() && newX < grid.size())
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
    int colCount = 0;
    
    for(int x =0; x < grid.size();x++)
    {
        if(grid[x][y] == 1)
        {
            colCount++;        
        }
    }
    
    if(colCount == grid.size())
    {
        return true;
    }
    
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

bool Game::IsWithinGrid(Block* block, int move_dir)
{
    std::cout << "BlockPos" <<  (block->pos.x/10 + move_dir) << std::endl;
    int newX,newY;
    
    for(int i =0;i<4;i++)
    {
        newX = block->pos.x / 10 + block->shape[i].x + move_dir;
        newY = block->pos.y / 10 + block->shape[i].y;
        
        if(newX < 0)
        {
            return false;
        }

        if(newY >= grid[0].size())
        {
            return false;
        }

        if(newX >= grid.size())
        {
            return false;
        }
    }
    // if(block->pos.x + move_dir < 0 || block->pos.x/10 + move_dir >= grid.size())
    // {
    //     return false;
    // }

    return true;
}
