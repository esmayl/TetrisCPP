#include <iostream>
#include "Game.h"
#include "Renderer.h"

Renderer renderer;

int main(int argc, char* args[]) 
{
	renderer.InitWindow();
	
	renderer.Render();

	return 0;
}