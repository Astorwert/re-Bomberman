#include "Bonus.h"

Bonus::Bonus(SDL_Texture *img, const int &p1, const int &p2) : Object(img, p1, p2) {
	h = 14;
	w = rand() % 3 + 1;
	symb = 's';
	prevent = false;
}

bool Bonus::tryDestroy(Game &game) { return true; }

int Bonus::tryCollect(Game &game) { return w; }

Bonus::~Bonus() {}
