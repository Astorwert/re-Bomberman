#include "Player2.h"

Player2::Player2(SDL_Texture *img, const int &p1, const int &p2) : Unit(img, p1, p2) {
	symb = 'P';
}

bool Player2::Action(Game &game) {

	move = 0;

	int tx = x, ty = y;

	if (game.act[119]) { //UP
		ty -= speed;
		direct = 0;
		move = 1;
	}
	if (game.act[115]) { //DOWN
		ty += speed;
		direct = 2;
		move = 1;
	}
	if (game.act[100]) { //RIGHT
		tx += speed;
		direct = 3;
		move = 1;
	}
	if (game.act[97]) { //LEFT
		tx -= speed;
		direct = 1;
		move = 1;
	}
	if (game.act[32] && cooldown <= 0 && game.check_collision_player({ x + 6, y + 29, 20, 17 }, 0)) {
		game.plant(x + 17, y + 32, range, 2);
		cooldown = maxcooldown;
	}

	int layer = 0;
	bool xstep = false, ystep = false, diagonal = false;


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

Player2::~Player2() {}
