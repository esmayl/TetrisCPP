#pragma once
#include <SDL.h>
#include <vector>
#include <chrono>
#include <math.h>
#include "Block.h"
#include "Game.h"

class Renderer
{
public:
    void InitWindow();
    void Render();
    void DrawPlayfield();
    void DrawBlock(int x, int y, int sizeX, int sizeY);
    void DrawBlock(Block* block);
    void CreateBlock(int r, int g, int b, int a);
private:
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const int cellSize = 10;
    const float edgeMargin = 0.5f;
    
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_FRect background;

    std::vector<Block> blocksFalling;

    double secondsPast = 0;
    Uint32 previousTicks;
    float deltaTime;
    Game* game;
};
