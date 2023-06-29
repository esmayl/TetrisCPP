#include "Renderer.h"

void Renderer::InitWindow()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not initialize: %s", SDL_GetError());
        return;
    }

    // Create a window
    window = SDL_CreateWindow("Window Renderer", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not create window: %s", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Create a renderer
    renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL could not create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    Renderer::CreateBlock(100,100,80,255);

    previousTicks = SDL_GetTicks();
}

void Renderer::Render()
{
    // Wait for user to close the window
    bool quit = false;
    SDL_Event event;
    int moveDir = 0;

    while (!quit) 
    {
        Uint32 currentTicks = SDL_GetTicks();

        deltaTime = (currentTicks - previousTicks) / 1000.0f;
        previousTicks = currentTicks;

        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_EVENT_QUIT) 
            {
                quit = true;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    secondsPast = 1;
                    break;
                }
                if (event.key.keysym.sym == SDLK_LEFT)
                {
                    secondsPast = 1;
                    moveDir = -1;
                    break;
                }
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    secondsPast = 1;
                    moveDir = 1;
                    break;
                }
            }
        }

        Renderer::DrawPlayfield();

        for (size_t i = 0; i < blocksFalling.size(); i++)
        {

            // Only move the blocks every 1 second, unless the down arrow is pressed above 
            if (secondsPast >= 1) 
            {

                // Check if the block has reached the floor
                if (blocksFalling[i].y < SCREEN_HEIGHT - cellSize) 
                {
                    secondsPast = 0;
                    
                    blocksFalling[i].MoveHorizontal(moveDir * cellSize);
                    moveDir = 0;

                    blocksFalling[i].MoveDown(cellSize);

                    // Check again to see if the block has reached the floor after the move, makes sure we only spawn a new block when the block hits the floor
                    if(blocksFalling[i].y >= SCREEN_HEIGHT - cellSize) 
                    {
                        Renderer::CreateBlock(100,200,80,255);
                    }
                }

            }
            else 
            {
                secondsPast += deltaTime;
            }

            Renderer::DrawBlock(&blocksFalling[i]);
        }

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Renderer::DrawPlayfield()
{
    // Set clear color
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black

    // Clear the renderer
    SDL_RenderClear(renderer);

    // Set the background color
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red

    background.x = SCREEN_WIDTH / 3;
    background.y = 0;
    background.h = SCREEN_HEIGHT;
    background.w = SCREEN_WIDTH / 3;

    SDL_RenderRect(renderer, &background);
}

void Renderer::DrawBlock(int x,int y,int sizeX,int sizeY) 
{
    int row = sizeof(playField->grid) / sizeof(playField->grid[0]);
    int collumns = sizeof(playField->grid[0]) / sizeof(playField->grid[0][0]);

    SDL_FRect drawRect;

    drawRect.h = sizeX;
    drawRect.w = sizeY;

    // Set the rect color
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Green

    drawRect.x = background.x + x;
    drawRect.y = background.y + y;

    SDL_RenderRect(renderer, &drawRect);
}

void Renderer::DrawBlock(Block* block)
{
    int row = sizeof(playField->grid) / sizeof(playField->grid[0]);
    int collumns = sizeof(playField->grid[0]) / sizeof(playField->grid[0][0]);

    SDL_FRect drawRect;

    drawRect.h = cellSize;
    drawRect.w = cellSize;

    // Set the rect color
    SDL_SetRenderDrawColor(renderer, block->r, block->g, block->b, block->a);  // Green

    drawRect.x = block->x;
    drawRect.y = block->y;

    SDL_RenderRect(renderer, &drawRect);
}


void Renderer::CreateBlock(int r,int g,int b,int a)
{
    Block newBlock(SCREEN_WIDTH / 2, 0,r,g,b,a);
    blocksFalling.push_back(newBlock);
}
