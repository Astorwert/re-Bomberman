#include "Wall.h"

Wall::Wall(SDL_Texture *img, const int &p1, const int &p2) : Object(img, p1, p2) {

	h = rand() % 3;
	w = 3;
	symb = 'w';
	col = true;
}

Wall::~Wall() {}