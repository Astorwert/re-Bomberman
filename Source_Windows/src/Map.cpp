#include <iostream>
#include <cstdlib>  
#include "SDL2\include\SDL.h"
#include "SDL2\include\SDL_image.h"
#include <list>  
#include "Map.h"
#include "Texture.h"

Map::Map() {}

void Map::drawMap(SDL_Texture *tileset, SDL_Texture *backg, SDL_Renderer *ren) const {

	renderTexture(backg, ren, 1120, 672, 0, 0);

	for (int i = 0; i < 19; i++) {

		if (i == 0) {
			for (int j = 0; j < 25; j++) {
				if (j == 0) renderTexture(tileset, ren, 160 + j * 32, 32 + i * 32, 0, 0, 1);
				else if (j == 24) renderTexture(tileset, ren, 160 + j * 32, 32 + i * 32, 0, 2, 1);
				else renderTexture(tileset, ren, 160 + j * 32, 32 + i * 32, 0, 1, 1);
			}
		}
		else if (i == 18) {
			for (int j = 0; j < 25; j++) {
				if (j == 0) renderTexture(tileset, ren, 160 + j * 32, 32 + i * 32, 2, 0, 1);
				else if (j == 24) renderTexture(tileset, ren, 160 + j * 32, 32 + i * 32, 2, 2, 1);
				else renderTexture(tileset, ren, 160 + j * 32, 32 + i * 32, 2, 1, 1);
			}
		}
		else {
			for (int j = 0; j < 25; j++) {
				if (j == 0) renderTexture(tileset, ren, 160 + j * 32, 32 + i * 32, 1, 0, 1);
				else if (j == 24) renderTexture(tileset, ren, 160 + j * 32, 32 + i * 32, 1, 2, 1);
				else renderTexture(tileset, ren, 160 + j * 32, 32 + i * 32, 1, 1, 1);
			}
		}
	}
	renderTexture(tileset, ren, 160 + 1 * 32, 32 + 1 * 32, 5, 4, 1);
	renderTexture(tileset, ren, 160 + 1 * 32, 32 + 17 * 32, 5, 4, 1);
	renderTexture(tileset, ren, 160 + 23 * 32, 32 + 1 * 32, 5, 4, 1);
	renderTexture(tileset, ren, 160 + 23 * 32, 32 + 17 * 32, 5, 4, 1);
}

Map::~Map(){}
