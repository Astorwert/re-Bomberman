#include <iostream>
#include <cstdlib>  
#include <fstream>
#include "SDL2\include\SDL.h"
#include "SDL2\include\SDL_image.h"
#include <list>
#include "Texture.h"
#include "Menu.h"

void Menu::create(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	win = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}
