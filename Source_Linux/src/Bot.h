#ifndef BOT_H
#define BOT_H

#include "Unit.h"
#include "Game.h"


/**
 * @brief									The class that represents one of the varieties of the game players - Bot
 */
class Bot : public Unit {
public:

	/**
	 * @brief								Standard constructor initializing bot unit object
	 *
	 * @param[in] SDL_Texture * img			object texture pointer
	 * @param[in] const int & y				coordinate for drawing the texture along the Y axis
	 * @param[in] const int & x				coordinate for drawing the texture along the X axis
	 */
	Bot(SDL_Texture *img, const int &y, const int &x);

	SDL_Rect getrect() const;

	/**
	 * @brief								Method that emits player activity
	 *
	 * @details								Calls a method to release movement, setting bombs, by AI
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the object is still alive and false otherwise
	 */
	bool Action(Game &game);

	~Bot();

};
#endif
