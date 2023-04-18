#include "Unit.h"

Unit::Unit(SDL_Texture *img, const int &p1, const int &p2) : Object(img, p1, p2) {
	direct = 0;
	move = 0;
	cooldown = maxcooldown;
	speed = 2;
	range = 2;
	col = true;
	prevent = false;
}

SDL_Rect Unit::getrect() const { return { x + 6, y + 29, 20, 17 }; }

void Unit::Draw(SDL_Renderer *ren, const int &frame) const {
	renderPlayer(tileset, ren, x, y, frame, direct, move);
}

bool Unit::Action(Game &game) {

	move = 0;

	int tx = x, ty = y;

	if (game.act[153]) { //UP
		ty -= speed;
		direct = 0;
		move = 1;
	}
	if (game.act[152]) { //DOWN
		ty += speed;
		direct = 2;
		move = 1;
	}
	if (game.act[150]) { //RIGHT
		tx += speed;
		direct = 3;
		move = 1;
	}
	if (game.act[151]) { //LEFT
		tx -= speed;
		direct = 1;
		move = 1;
	}
	if (game.act[159] && cooldown <= 0 && game.check_collision_player({ x + 6, y + 29, 20, 17 }, 0)) {
		game.plant(x + 17, y + 32, range, 1);
		cooldown = maxcooldown;
	}

	int layer = 0;
	bool xstep = false, ystep = false;

	if (!game.check_collision_player({ x + 6, y + 29, 20, 17 }, 0)) layer = 1;

	if (game.check_collision_player({ x + 6, ty + 29, 20, 17 }, layer) && ty >= 32 && ty <= 560) ystep = true;

	if (game.check_collision_player({ tx + 6, y + 29, 20, 17 }, layer) && tx >= 185 && tx <= 905) xstep = true;

	if (xstep && ystep) {
		if (game.check_collision_player({ tx + 6, ty + 29, 20, 17 }, layer)) {
			x = tx;
			y = ty;
		}
	}
	else {
		if (xstep) x = tx;
		if (ystep) y = ty;
	}

	int effect = game.look_drop({ x + 6, y + 29, 20, 17 });
	if (effect == 1 && maxcooldown > 20) maxcooldown = maxcooldown / 2;
	if (effect == 2 && speed < 5) speed++;
	if (effect == 3 && range < 9) range++;

	cooldown--;
	return 0;
}

bool Unit::tryDestroy(Game &game) {
	game.death(x, y);
	return true;
}

Unit::~Unit() {}
