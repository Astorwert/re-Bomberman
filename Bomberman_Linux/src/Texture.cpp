#include <iostream>
#include <stdio.h> 
#include <stdlib.h>  
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Texture.h"

using namespace std;

SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren) {
	SDL_Texture *texture = IMG_LoadTexture(ren, file.c_str());
	return texture;
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, const int &x, const int &y, const int &h, const int &w) {

	SDL_Rect srcrect = { 0 , 0, 1600, 900 };
	SDL_Rect dstrect = { h, w, x, y };

	SDL_RenderCopy(ren, tex, &srcrect, &dstrect);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, const int &x, const int &y, const int &h, const int &w, const int &frame) {

	SDL_Rect srcrect = { frame* w * 17, h * 17, 16, 16 };
	SDL_Rect dstrect = { x, y, 32, 32 };

	SDL_RenderCopy(ren, tex, &srcrect, &dstrect);
}

void renderPlayer(SDL_Texture *tex, SDL_Renderer *ren, const int &x, const int &y, const int &sprite, const int &direct, const int &move) {

	SDL_Rect srcrect = { sprite * 17 * move, (direct) * 25, 17, 25 };
	SDL_Rect dstrect = { x, y, 34, 50 };

	SDL_RenderCopy(ren, tex, &srcrect, &dstrect);
}
