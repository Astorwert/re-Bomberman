#include "Bot.h"

Bot::Bot(SDL_Texture *img, const int &p1, const int &p2) : Unit(img, p1, p2) {
	
	symb = 'Q';
	col = true;

}

SDL_Rect Bot::getrect() const { return { x + 6, y + 32, 18, 17  }; }

bool Bot::Action(Game &game) {
	int layer = 0;
	

	while (!game.check_collision_player({ x + 6, y + 29, 20, 17 }, layer)) {
		layer++;
	}

	int tx = x, ty = y;
	move = 0;

	if ((x + 16) % 32 > 13 && (x + 16) % 32 < 19 && (y + 39) % 32 > 13 && (y + 39) % 32 < 19) {

		int state = game.try_escape({ x + 16, y + 30, 1, 1 }, range);
		if (state == 0) { move = 1; direct = 0; ty -= speed; }
		else if (state == 1) { move = 1; direct = 2; ty += speed; }
		else if (state == 2) { move = 1; direct = 1; tx -= speed; }
		else if (state == 3) { move = 1; direct = 3; tx += speed; }
		else if (state == 4) {
			state = game.search_object({ x + 16, y + 39, 1, 1 }, 1);
			if (state == 0) { move = 1; direct = 0; ty -= speed; }
			else if (state == 1) { move = 1; direct = 2; ty += speed; }
			else if (state == 2) { move = 1; direct = 1; tx -= speed; }
			else if (state == 3) { move = 1; direct = 3; tx += speed; }
			else if (state == 4 && cooldown < -5 && game.check_collision_player({ x + 6, y + 29, 20, 17 }, 0)) {
				game.plant(x + 17, y + 30, range, 0);
				cooldown = maxcooldown;
			}
			else if (state == 5) {
				state = game.search_object({ x + 16, y + 39, 1, 1 }, 2);
				if (state == 0) { move = 1; direct = 0; ty -= speed; }
				else if (state == 1) { move = 1; direct = 2; ty += speed; }
				else if (state == 2) { move = 1; direct = 1; tx -= speed; }
				else if (state == 3) { move = 1; direct = 3; tx += speed; }
				else if (state == 4 && cooldown < -5 && game.check_collision_player({ x + 6, y + 29, 20, 17 }, 0)) {
					game.plant(x + 17, y + 30, range, 0);
					cooldown = maxcooldown;
				}
			}
		}
	}
	else {
		move = 1;
		if (direct == 0) { ty -= speed; }
		else if (direct == 2) { ty += speed; }
		else if (direct == 1) { tx -= speed; }
		else if (direct == 3) { tx += speed; }
	}
	if (game.check_collision_player({ tx + 6, ty + 29, 20, 17 }, layer) && ty >= 32 && ty <= 560 && tx >= 185 && tx <= 905) {
		x = tx;
		y = ty;
	}
	else {
		if (cooldown <= 0) {
			game.plant(x + 17, y + 30, range, 0);
			cooldown = maxcooldown;
		}
		if (direct == 0) { direct = 2; }
		else if (direct == 2) { direct = 0; }
		else if (direct == 1) { direct = 3; }
		else if (direct == 3) { direct = 1; }
	}

	int effect = game.look_drop({ x + 16, y + 39, 1, 1 });
	if (effect == 1) maxcooldown = maxcooldown / 2;
	if (effect == 2) speed++;
	if (effect == 3) range++;

	cooldown--;
	return 0;
}

Bot::~Bot() {}
