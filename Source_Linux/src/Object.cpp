#include "Object.h"
#include "Game.h"


Object::Object(SDL_Texture *img, const int &p1, const int &p2) {
	y = p1;
	x = p2;
	col = false;
	symb = '.';
	tileset = img;
	prevent = true;
}

void Object::Draw(SDL_Renderer *ren, const int &frame) const {
	renderTexture(tileset, ren, x, y, h, w, 1);
}

bool Object::Action(Game &game) { return 0; }

bool Object::tryDestroy(Game &game) { return 0; }

int Object::tryCollect(Game &game) { return -1; }

bool Object::catchFlame() const { return prevent; }

char Object::getchar() const { return symb; }

bool Object::getcol() const { return col; }

SDL_Rect Object::getrect() const { return { x, y, 32, 32 }; }

Object::~Object() {}