#ifndef PLAYER2_H
#define PLAYER2_H

#include "Unit.h"
#include "Game.h"

/**
 * @brief									The class that represents one of the varieties of the parent class Unit - Player2
 */
class Player2 : public Unit {
public:

	/**
	 * @brief								Standard constructor initializing Player class object
	 *
	 * @param[in] SDL_Texture * img			object texture pointer
	 * @param[in] const int & y				coordinate for drawing the texture along the Y axis
	 * @param[in] const int & x				coordinate for drawing the texture along the X axis
	 */
	Player2(SDL_Texture *img, const int &x, const int &y);

	/**
	 * @brief								Method that emits Unit activity
	 *
	 * @details								Calls a method to place bomb or get bonuses, verifies that a unit has obstacles and has a unique control
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the object is still active and false otherwise
	 */
	bool Action(Game &game);

	~Player2();

};

#endif