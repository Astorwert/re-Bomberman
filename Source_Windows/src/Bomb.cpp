#include "Bomb.h"

Bomb::Bomb(SDL_Texture *img, const int &p1, const int &p2, const int &e, const int &r, const int &num) : Object(img, p1, p2) {
	lifetime = e;
	h = 4;
	w = 1;
	range = r;
	symb = (char)range;
	col = true;
	n = num;
	prevent = false;
}

bool Bomb::tryDestroy(const Game &game) {
	lifetime = 0;
	return false;
}

void Bomb::Draw(SDL_Renderer *ren, const int &frame) const {
	renderTexture(tileset, ren, x, y, h, w, frame);
}

bool Bomb::Action(Game &game) {
	if (lifetime-- <= 0) {
		game.boom(x, y, range, n);
		return 1;
	}
	return 0;
}

Bomb::~Bomb() {}
