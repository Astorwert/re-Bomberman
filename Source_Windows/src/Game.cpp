#include <iostream>
#include <cstdlib>  
#include <fstream>
#include "SDL2\include\SDL.h"
#include "SDL2\include\SDL_image.h"
#include <vector>
#include <list>
#include <queue>
#include "Texture.h"
#include "Player1.h"
#include "Player2.h"
#include "Bonus.h"
#include "Bot.h"
#include "DesPlayer.h"
#include "Bomb.h"
#include "Flame.h"
#include "Wall.h"
#include "Bar.h"
#include "DesBar.h"
#include "Game.h"

//static const int FIX_NUMKEY = 1073741753;

Game::Game() {}

void Game::loadMenu(const char* title, const int &xpos, const int &ypos, const int &width, const int &height, const int &flags) {
	win = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	icon = IMG_Load("src/images/icon.jpg");
	SDL_SetWindowIcon(win, icon);

	Channel1 = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	Channel2 = SDL_OpenAudioDevice(NULL, 0, &wavSpec1, NULL, 0);
	Channel3 = SDL_OpenAudioDevice(NULL, 0, &wavSpec2, NULL, 0);


	SDL_LoadWAV("src/sounds/Powerup.wav", &wavSpec, &wavPowerup, &wavLength);
	SDL_LoadWAV("src/sounds/Death.wav", &wavSpec1, &wavDeath, &wavLength1);
	SDL_LoadWAV("src/sounds/Explosion.wav", &wavSpec2, &wavExplosion, &wavLength2);

	tileset = loadTexture("src/images/Tileset.png", ren);
	menu = loadTexture("src/images/Menu.jpg", ren);
	bomb = loadTexture("src/images/Bomb.png", ren);
	backg = loadTexture("src/images/background.jpg", ren);
	tilesetplayer = loadTexture("src/images/Man.png", ren);
	tilesetdeath = loadTexture("src/images/Death.png", ren);

	menuRun = true;

	for (int i = 0; i < 322; i++) act[i] = false;

}

void Game::start() {

	gameRun = true;
	menuRun = false;

	obj.push_back(make_shared <Player1>(tilesetplayer, 48, 896));
	if (point_state == 1) obj.push_back(make_shared <Player2>(tilesetplayer, 554, 194));
	if (point_state == 0) obj.push_back(make_shared <Bot>(tilesetplayer, 554, 194));
	obj.push_back(make_shared <Bot>(tilesetplayer, 48, 192));
	obj.push_back(make_shared <Bot>(tilesetplayer, 554, 896));

	fin.open ("src/config/Map.txt");
	fout.open ("src/config/Score.txt");

	char x;
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 23; j++) {
			fin >> x;
			if (x == 'w') {
				obj.push_back(make_shared <Wall>(tileset, i * 32 + 64, j * 32 + 192));
			}
			else if (x == 'b') {
				obj.push_back(make_shared <Bar>(tileset, i * 32 + 64, j * 32 + 192));
			}
			else if (x == '.' && rand() % 2 == 0) {
				obj.push_back(make_shared <Bar>(tileset, i * 32 + 64, j * 32 + 192));
			}
		}
	}
}

void Game::handleEvents() {
	ticks = SDL_GetTicks();
	time = ticks / 200;
	sprite = time % 4;

	while (SDL_PollEvent(&event)) { 

		switch (event.type) {
		case SDL_QUIT:
			if (point_state == 0) {
				fout << "Solo Game Mode :" << endl;
				fout << "Player - " << score1 << endl;
			}
			if (point_state == 1) {
				fout << "Coop Game Mode :" << endl;
				fout << "FirstPlayer (WASD) - " << score2 << endl;
				fout << "SecondPlayer (Arrows) - " << score1 << endl;
			}
			gameRun = false;
			menuRun = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym > 200) act[event.key.keysym.sym - 1073741753] = true;
			else act[event.key.keysym.sym] = true;
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym > 200) act[event.key.keysym.sym - 1073741753] = false;
			else act[event.key.keysym.sym] = false;
			break;
		}
	}
}

void Game::update() {

	if (ticks - old_ticks >= 10) {

		old_ticks = ticks;

		if (gameRun) {
			if (act[SDLK_ESCAPE]) {
				presed = true;
			}
			if (!act[SDLK_ESCAPE] && presed) {
				presed = false;

				for (auto it = obj.begin(); it != obj.end(); ++it) {
					it = obj.erase(it);
				}
				obj.clear();

				if (point_state == 0) {
					fout << "Solo Game Mode :" << endl;
					fout << "Player - " << score1 << endl;
				}
				if (point_state == 1) {
					fout << "Coop Game Mode :" << endl;
					fout << "FirstPlayer (WASD) - " << score2 << endl;
					fout << "SecondPlayer (Arrows) - " << score1 << endl;
				}

				fin.close();
				fout.close();
				gameRun = false;
				menuRun = true;
			}

			for (auto it = obj.begin(); it != obj.end(); ++it) {
				if ((*it)->Action(*this)) {
					it = obj.erase(it);
				}
			}
			for (int i = 0; i < 17; i++) {
				for (int j = 0; j < 23; j++) {
					vec[i][j] = '.';
					vec2[i][j] = '.';
				}
			}
			for (auto it = obj.begin(); it != obj.end(); it++) {

				SDL_Rect t = (*it)->getrect();
				if ((*it)->getchar() > 9) {
					vec[(t.y - 64) / 32][(t.x - 192) / 32] = (*it)->getchar();
				}
				else {
					vec[(t.y - 64) / 32][(t.x - 192) / 32] = 'B';
					int range = (int)(*it)->getchar();
					int y = (t.y - 64) / 32;
					int x = (t.x - 192) / 32;

					vec2[y][x] = 'f';
					for (int i = 1; i <= range && x + i < 23; i++) {
						if (vec[y][x + i] != 'w' && vec[y][x + i] != 'b') vec2[y][x + i] = 'f';
						else break;
					}
					for (int i = 1; i <= range && x - i >= 0; i++) {
						if (vec[y][x - i] != 'w' && vec[y][x - i] != 'b') vec2[y][x - i] = 'f';
						else break;
					}
					for (int i = 1; i <= range && y + i < 17; i++) {
						if (vec[y + i][x] != 'w' && vec[y + i][x] != 'b') vec2[y + i][x] = 'f';
						else break;
					}
					for (int i = 1; i <= range && y - i >= 0; i++) {
						if (vec[y - i][x] != 'w' && vec[y - i][x] != 'b') vec2[y - i][x] = 'f';
						else break;
					}
				}
			}
		}
		else {
			if (act[153] && point_state > 0) {
				point_state--;
			}
			if (act[152] && point_state < 1) { //DOWN
				point_state++;
			}
			if (act[13]) {
				gameRun = true;
				menuRun = false;
				start();
			}
		}
	}
}

void Game::render() const {

	SDL_RenderClear(ren);

	if (gameRun) {
		map->drawMap(tileset, backg, ren);

		for (auto it = obj.rbegin(); it != obj.rend(); it++) {
			(*it)->Draw(ren, sprite);
		}
	}
	else if (menuRun) {
		renderTexture(menu, ren, 1120, 672, 0, 0);
		if (point_state == 0) renderTexture(bomb, ren, 48, 48, 280, 475);
		else if (point_state == 1) renderTexture(bomb, ren, 48, 48, 280, 530);
	}

	SDL_RenderPresent(ren);

}

void Game::clean() const {

	SDL_CloseAudioDevice(Channel1);
	SDL_CloseAudioDevice(Channel2);
	SDL_CloseAudioDevice(Channel3);
	SDL_FreeWAV(wavPowerup);
	SDL_FreeWAV(wavDeath);
	SDL_FreeWAV(wavExplosion);
	SDL_DestroyTexture(bomb);
	SDL_DestroyTexture(menu);
	SDL_DestroyTexture(backg);
	SDL_DestroyTexture(tileset);
	SDL_DestroyTexture(tilesetplayer);
	SDL_DestroyTexture(tilesetdeath);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

bool Game::running() const {
	return (gameRun || menuRun);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void Game::plant(const int &x, const int &y, const int &range, const int &num) {
	obj.push_back(make_shared <Bomb>(tileset, (y / 32) * 32, (x / 32) * 32, 100, range, num));
}

void Game::drop_Bonus(const int &x, const int &y) {
	obj.push_back(make_shared <Bonus>(tileset, y, x));
}

void Game::boom(const int &x, const int &y, const int &range, const int &num) {
	/*if (Channel2) {
		SDL_ClearQueuedAudio(Channel2 && Channel2 <= 4);
		SDL_QueueAudio(Channel2, wavExplosion, wavLength2);
		SDL_PauseAudioDevice(Channel2, 0);
	}*/

	obj.push_back(make_shared <Flame>(tileset, y, x, 40, 12, num));

	for (int i = 0; i <= range; i++) {
		SDL_Rect sq = { (x + 32 * i) , y , 32, 32 };
		if (check_collision_flame(sq, num) && x + 32 * i - 32 < 895) {
			if (i == range) {
				obj.push_back(make_shared <Flame>(tileset, y, x + 32 * i, 40, 9, num));
			}
			else if (i != 0) {
				obj.push_back(make_shared <Flame>(tileset, y, x + 32 * i, 40, 11, num));
			}
		}
		else break;
	}
	for (int i = 0; i >= -range; i--) {
		SDL_Rect sq = { (x + 32 * i) , y , 32, 32 };
		if (check_collision_flame(sq, num) && x + 32 * i >= 180) {
			if (i == -range) {
				obj.push_back(make_shared <Flame>(tileset, y, x + 32 * i, 40, 8, num));
			}
			else if (i != 0) {
				obj.push_back(make_shared <Flame>(tileset, y, x + 32 * i, 40, 11, num));
			}
		}
		else break;
	}
	for (int i = 0; i <= range; i++) {
		SDL_Rect sq = { x , y + 32 * i , 32, 32 };
		if (check_collision_flame(sq, num) && y + 32 * i - 32 < 560) {
			if (i == range) {
				obj.push_back(make_shared <Flame>(tileset, y + 32 * i, x, 40, 7, num));
			}
			else if (i != 0) {
				obj.push_back(make_shared <Flame>(tileset, y + 32 * i, x, 40, 10, num));
			}
		}
		else break;
	}
	for (int i = 0; i >= -range; i--) {
		SDL_Rect sq = { x , y + 32 * i , 32, 32 };
		if (check_collision_flame(sq, num) && y + 32 * i > 32) {
			if (i == -range) {
				obj.push_back(make_shared <Flame>(tileset, y + 32 * i, x, 40, 6, num));
			}
			else if (i != 0) {
				obj.push_back(make_shared <Flame>(tileset, y + 32 * i, x, 40, 10, num));
			}
		}
		else break;
	}

}

void Game::destroy_bar(const int &x, const int &y) {
	obj.push_back(make_shared <DesBar>(tileset, y, x, 50));
}

void Game::death(const int &x, const int &y) {
	/*if (Channel3 && Channel3 <= 4) {
		SDL_ClearQueuedAudio(Channel3);
		SDL_QueueAudio(Channel3, wavDeath, wavLength1);
		SDL_PauseAudioDevice(Channel3, 0);
	}*/
	obj.push_front(make_shared <DesPlayer>(tilesetdeath, y - 10, x, 80));
}

bool Game::check_collision_flame(const SDL_Rect &A, const int &num) {

	for (auto it = obj.begin(); it != obj.end(); ++it) {
		SDL_Rect B = (*it)->getrect();
		bool k = false;

		if (((*it)->getchar() != 'f') && !(A.x + A.w <= B.x || A.x >= B.x + B.w || A.y + A.h <= B.y || A.y >= B.y + B.h)) {

			if ((*it)->catchFlame()) k = true;

			if ((*it)->tryDestroy(*this)) {
				if (num == 1) score1 += 10;
				else if (num == 2) score2 += 10;
				it = obj.erase(it);
			}

			if (k) return false;
		}
	}

	return true;
}

bool Game::check_collision_player(const SDL_Rect &A, const int &fix) const {
	int k = 0;
	for (auto it = obj.begin(); it != obj.end(); it++) {

		SDL_Rect B = (*it)->getrect();
		if (!(A.x + A.w <= B.x || A.x >= B.x + B.w || A.y + A.h <= B.y || A.y >= B.y + B.h)) {
			if ((*it)->getcol() && ++k > 1 + fix) return false;
		}
	}
	return true;
}

int  Game::look_drop(const SDL_Rect &A) {
	int type = 0;
	for (auto it = obj.begin(); it != obj.end(); ++it) {

		SDL_Rect B = (*it)->getrect();
		if (!(A.x + A.w <= B.x || A.x >= B.x + B.w || A.y + A.h <= B.y || A.y >= B.y + B.h)) {
			type = (*it)->tryCollect(*this);
			if (type != -1) {
				/*if (Channel1 && Channel1 <= 4) {
					SDL_ClearQueuedAudio(Channel1);
					SDL_QueueAudio(Channel1, wavPowerup, wavLength);
					SDL_PauseAudioDevice(Channel1, 0);
				}*/
				it = obj.erase(it);
				return type;
			}
		}
	}
	return 0;
}

int  Game::search_object(const SDL_Rect &A, const int &mode) const {
	int x = (A.x - 192) / 32;
	int y = (A.y - 64) / 32;

	char tmp[17][23];
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 23; j++) {
			tmp[i][j] = '.';
		}
	}

	if (mode == 1) {
		if (vec[y][x] == 'P') { return 4; }
		if (y + 1 < 17 && (vec[y + 1][x] == 'P' || vec[y + 1][x] == 'Q')) { return 4; }
		if (y - 1 >= 0 && (vec[y - 1][x] == 'P' || vec[y - 1][x] == 'Q')) { return 4; }
		if (x + 1 < 23 && (vec[y][x + 1] == 'P' || vec[y][x + 1] == 'Q')) { return 4; }
		if (x - 1 >= 0 && (vec[y][x - 1] == 'P' || vec[y][x - 1] == 'Q')) { return 4; }
	}
	else {
		if (vec[y][x] == 'b') { return 4; }
		if (y + 1 < 17 && vec[y + 1][x] == 'b') { return 4; }
		if (y - 1 >= 0 && vec[y - 1][x] == 'b') { return 4; }
		if (x + 1 < 23 && vec[y][x + 1] == 'b') { return 4; }
		if (x - 1 >= 0 && vec[y][x - 1] == 'b') { return 4; }
	}

	tmp[y][x] = 'x';

	queue<pair<int, int>> fronta({ make_pair(x,y) });

	while (!fronta.empty()) {
		x = fronta.front().first;
		y = fronta.front().second;

		if (mode == 1) {
			if (y + 1 < 17 && (vec[y + 1][x] == 'P' || vec[y + 1][x] == 's' || (vec[y + 1][x] == 'Q' && tmp[y + 1][x] != 'x'))) { tmp[y + 1][x] = 'u'; y++; break; }
			if (y - 1 >= 0 && (vec[y - 1][x] == 'P' || vec[y - 1][x] == 's' || (vec[y - 1][x] == 'Q' && tmp[y - 1][x] != 'x'))) { tmp[y - 1][x] = 'd'; y--; break; }
			if (x + 1 < 23 && (vec[y][x + 1] == 'P' || vec[y][x + 1] == 's' || (vec[y][x + 1] == 'Q' && tmp[y][x + 1] != 'x'))) { tmp[y][x + 1] = 'l'; x++; break; }
			if (x - 1 >= 0 && (vec[y][x - 1] == 'P' || vec[y][x - 1] == 's' || (vec[y][x - 1] == 'Q' && tmp[y][x - 1] != 'x'))) { tmp[y][x - 1] = 'r'; x--; break; }
		}
		else {
			if (y + 1 < 17 && (vec[y + 1][x] == 'b')) { break; }
			if (y - 1 >= 0 && (vec[y - 1][x] == 'b')) { break; }
			if (x + 1 < 23 && (vec[y][x + 1] == 'b')) { break; }
			if (x - 1 >= 0 && (vec[y][x - 1] == 'b')) { break; }
		}

		if (y + 1 < 17 && tmp[y + 1][x] == '.' && vec[y + 1][x] == '.' && vec2[y + 1][x] == '.') { tmp[y + 1][x] = 'u'; fronta.push(make_pair(x, y + 1)); }
		if (y - 1 >= 0 && tmp[y - 1][x] == '.' && vec[y - 1][x] == '.' && vec2[y - 1][x] == '.') { tmp[y - 1][x] = 'd'; fronta.push(make_pair(x, y - 1)); }
		if (x + 1 < 23 && tmp[y][x + 1] == '.' && vec[y][x + 1] == '.' && vec2[y][x + 1] == '.') { tmp[y][x + 1] = 'l'; fronta.push(make_pair(x + 1, y)); }
		if (x - 1 >= 0 && tmp[y][x - 1] == '.' && vec[y][x - 1] == '.' && vec2[y][x - 1] == '.') { tmp[y][x - 1] = 'r'; fronta.push(make_pair(x - 1, y)); }

		fronta.pop();
	}
	if (fronta.empty()) return 5;

	while (1) {
		if (tmp[y][x] == 'l' && tmp[y][x - 1] != 'x') x--;
		else if (tmp[y][x] == 'r' && tmp[y][x + 1] != 'x') x++;
		else if (tmp[y][x] == 'u' && tmp[y - 1][x] != 'x') y--;
		else if (tmp[y][x] == 'd' && tmp[y + 1][x] != 'x') y++;
		else break;
	}

	if (tmp[y][x] == 'l') return 3;
	if (tmp[y][x] == 'r') return 2;
	if (tmp[y][x] == 'u') return 1;
	if (tmp[y][x] == 'd') return 0;
	if (tmp[y][x] == 'x') return 4;
}

int  Game::try_escape(const SDL_Rect &A, const int &range) const {
	int x = (A.x - 192) / 32;
	int y = (A.y - 64) / 32;

	char tmp[17][23];
	for (int i = 0; i < 17; i++) {
		for (int j = 0; j < 23; j++) {
			tmp[i][j] = '.';
		}
	}

	queue<pair<int, int>> fronta({ make_pair(x,y) });

	if (vec2[y][x] != 'f') return 4;
	tmp[y][x] = 'x';

	while (!fronta.empty()) {
		x = fronta.front().first;
		y = fronta.front().second;

		if (y + 1 < 17 && vec2[y + 1][x] == '.' && (vec[y + 1][x] == '.' || vec[y + 1][x] == 's' || vec[y + 1][x] == 'e')) { tmp[y + 1][x] = 'u'; y++;  break; }
		if (y - 1 >= 0 && vec2[y - 1][x] == '.' && (vec[y - 1][x] == '.' || vec[y - 1][x] == 's' || vec[y - 1][x] == 'e')) { tmp[y - 1][x] = 'd'; y--;  break; }
		if (x + 1 < 23 && vec2[y][x + 1] == '.' && (vec[y][x + 1] == '.' || vec[y][x + 1] == 's' || vec[y][x + 1] == 'e')) { tmp[y][x + 1] = 'l'; x++;  break; }
		if (x - 1 >= 0 && vec2[y][x - 1] == '.' && (vec[y][x - 1] == '.' || vec[y][x - 1] == 's' || vec[y][x - 1] == 'e')) { tmp[y][x - 1] = 'r'; x--;  break; }

		if (y + 1 < 17 && tmp[y + 1][x] == '.' && (vec[y + 1][x] == '.' || vec[y + 1][x] == 's' || vec[y + 1][x] == 'e')) { tmp[y + 1][x] = 'u'; fronta.push(make_pair(x, y + 1)); }
		if (y - 1 >= 0 && tmp[y - 1][x] == '.' && (vec[y - 1][x] == '.' || vec[y - 1][x] == 's' || vec[y - 1][x] == 'e')) { tmp[y - 1][x] = 'd'; fronta.push(make_pair(x, y - 1)); }
		if (x + 1 < 23 && tmp[y][x + 1] == '.' && (vec[y][x + 1] == '.' || vec[y][x + 1] == 's' || vec[y][x + 1] == 'e')) { tmp[y][x + 1] = 'l'; fronta.push(make_pair(x + 1, y)); }
		if (x - 1 >= 0 && tmp[y][x - 1] == '.' && (vec[y][x - 1] == '.' || vec[y][x - 1] == 's' || vec[y][x - 1] == 'e')) { tmp[y][x - 1] = 'r'; fronta.push(make_pair(x - 1, y)); }

		fronta.pop();
	}

	if (fronta.empty()) return 4;

	while (1) {
		if (tmp[y][x] == 'l' && tmp[y][x - 1] != 'x') x--;
		else if (tmp[y][x] == 'r' && tmp[y][x + 1] != 'x') x++;
		else if (tmp[y][x] == 'u' && tmp[y - 1][x] != 'x') y--;
		else if (tmp[y][x] == 'd' && tmp[y + 1][x] != 'x') y++;
		else break;
	}

	if (tmp[y][x] == 'l') return 3;
	if (tmp[y][x] == 'r') return 2;
	if (tmp[y][x] == 'u') return 1;
	if (tmp[y][x] == 'd') return 0;
	if (tmp[y][x] == 'x') return 4;
}

Game::~Game() {}
