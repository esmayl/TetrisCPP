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
    
    previousTicks = SDL_GetTicks();

    game = new Game(SCREEN_WIDTH/cellSize, SCREEN_HEIGHT/cellSize);
    
    Renderer::CreateBlock(100,100,80,255);
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

        Vector2 gridSize = Vector2(game->grid.size(),game->grid[0].size());

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


        // Only redraw the screen every second

        if (secondsPast >= 1) 
        {
            secondsPast = 0;
            
            for (size_t i = 0; i < blocksFalling.size(); i++)
            {
                Renderer::DrawPlayfield();

                // Check if the block has reached the floor
                if (blocksFalling[i].canMove && !game->CheckIfReachedEnd(blocksFalling[i].pos / cellSize,blocksFalling[i].shape)) 
                {
                    if(blocksFalling[i].pos.x -moveDir * cellSize < background.x + (cellSize * 2))
                    {
                        moveDir = 0;
                    }
                    
                    blocksFalling[i].Move(cellSize, moveDir * cellSize);
                    game->SetGridBlock(&blocksFalling[i],cellSize, moveDir);

                    moveDir = 0;

                    if(game->CheckIfReachedEnd(blocksFalling[i].pos / cellSize,blocksFalling[i].shape))
                    {
                        Renderer::CreateBlock(100,200,80,255);
                    
                        blocksFalling[i].canMove = false;
                    }

                    // if(game->CheckIfFullRow(blocksFalling[i].pos.y / cellSize,blocksFalling[i].shape))
                    // {
                    //     // remove row at blocksFalling[i].pos.y / cellSize
                    //     blocksFalling.erase(blocksFalling.begin() + i);
                    //     // move rows above the remove row down
                    //     // add score
                    // }
                }
        
                for (size_t i =0;i < gridSize.x;i++)
                {
                    for (size_t j=0;j < gridSize.y;j++)
                    {
                        if(game->grid[i][j] == 1)
                        {
                            Renderer::DrawBlock(i * cellSize, j * cellSize, cellSize, cellSize);
                        }
                    }
                }
            }
            
            // Update the screen
            SDL_RenderPresent(renderer);
        }
        
        secondsPast += deltaTime;
        

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
    SDL_FRect drawRect;

    drawRect.h = cellSize;
    drawRect.w = cellSize;

    // Set the rect color
    SDL_SetRenderDrawColor(renderer, 255, 0,0, 255);  // Green

    drawRect.x = x;
    drawRect.y = y;

    SDL_RenderRect(renderer, &drawRect);

}

void Renderer::DrawBlock(Block* block)
{
    int row = sizeof(block->shape) / sizeof(block->shape[0]);

    SDL_FRect drawRect;

    drawRect.h = cellSize;
    drawRect.w = cellSize;

    // Set the rect color
    SDL_SetRenderDrawColor(renderer, block->r, block->g, block->b, block->a);

    for (size_t i = 0; i < row; i++)
    {
        drawRect.x = ceil(block->pos.x + block->shape[i].x * cellSize);
        drawRect.y = ceil(block->pos.y + block->shape[i].y * cellSize);

        SDL_RenderRect(renderer, &drawRect);
    }


    //drawRect.x = block->pos.x;
    //drawRect.y = block->pos.y;

    //SDL_RenderRect(renderer, &drawRect);
}


void Renderer::CreateBlock(int r,int g,int b,int a)
{
    Block newBlock(SCREEN_WIDTH / 2, 0,r,g,b,a,static_cast<BlockTypes>(rand() % 4));
    blocksFalling.push_back(newBlock);
    
    game->SetGridBlock(&newBlock,cellSize, 0);
}
