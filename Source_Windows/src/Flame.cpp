#include "Flame.h"

Flame::Flame(SDL_Texture *img, const int &p1, const int &p2, const int &e, const int &direct, const int &num) : Bomb(img, p1, p2, e, range, num) {
	maxlifetime = e;
	lifetime = e;
	h = direct;
	symb = 'f';
	col = false;
	prevent = false;
}

void Flame::Draw(SDL_Renderer *ren, const int &frame) const {
	renderTexture(tileset, ren, x, y, h, w, (maxlifetime - lifetime) / ((maxlifetime) / 5));
}

bool Flame::Action(Game &game) {
	SDL_Rect sq = { x, y, 32, 32 };
	game.check_collision_flame(sq, n);
	return lifetime-- <= 0;
}

Flame::~Flame() {}
