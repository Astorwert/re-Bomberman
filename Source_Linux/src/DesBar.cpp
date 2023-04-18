#include "DesBar.h"

DesBar::DesBar(SDL_Texture *img, const int &p1, const int &p2, const int &e) : Bar(img, p1, p2) {
	h = 13;
	w = 1;
	maxlifetime = e;
	lifetime = e;
	symb = 'b';
	col = true;
}

void DesBar::Draw(SDL_Renderer *ren, const int &frame) const {
	renderTexture(tileset, ren, x, y, h, w, (maxlifetime - lifetime) / ((maxlifetime) / 5));
}

bool DesBar::Action(Game &game) {
	if (!(lifetime--)) {
		if (rand() % 6 == 0) game.drop_Bonus(x, y);
		return true;
	}
	return false;
}

DesBar::~DesBar() {}