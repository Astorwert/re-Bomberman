#include "DesPlayer.h"

DesPlayer::DesPlayer(SDL_Texture *img, const int &p1, const int &p2, const int &e) : Object(img, p1, p2) {
	h = 0;
	w = 1;
	maxlifetime = e;
	lifetime = e;
	symb = 'b';
	col = true;
	prevent = false;
}

void DesPlayer::Draw(SDL_Renderer *ren, const int &frame) const {
	renderPlayer(tileset, ren, x, y + 6, (maxlifetime - lifetime) / ((maxlifetime) / 8), 0, 1);
}

bool DesPlayer::Action(Game &game) {
	return lifetime-- == 0;
}

DesPlayer::~DesPlayer() {}