#include "Bar.h"

Bar::Bar(SDL_Texture *img, const int &p1, const int &p2) : Object(img, p1, p2) {
	h = rand() % 5;
	w = 4;
	symb = 'b';
	col = true;
}

bool Bar::tryDestroy(Game &game) {
	game.destroy_bar(x, y);
	return true;
}

Bar::~Bar() {}