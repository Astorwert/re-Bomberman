#include <iostream>
#include <iomanip>
#include <cstdlib>  
#include <fstream>
#include "SDL2\include\SDL.h"
#include "SDL2\include\SDL_image.h"
#include <vector>
#include <list>
#include <ctime>  
#include "Object.h"
#include "Game.h"

using namespace std;

int main(int argc, char * argv[]) {

	srand(static_cast<unsigned int>(time(NULL)));

	SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO);

	shared_ptr<Game> game = make_shared<Game>();

	game->loadMenu("Bomberman", 0, 30, 1120, 672, SDL_WINDOW_SHOWN);

	while (game->running()) {

		game->handleEvents();

		game->update();

		game->render();

	}

	game->clean();

	return 0;
}
