#ifndef UNIT_H
#define UNIT_H

#include "Object.h"
#include "Game.h"

/**
 * @brief									The class that represents basic methods of the parent class - Unit
 */
class Unit : public Object {
public:

	/**
	 * @brief								Standard constructor initializing Unit class object
	 *
	 * @param[in] SDL_Texture * img			object texture pointer
	 * @param[in] const int & y				coordinate for drawing the texture along the Y axis
	 * @param[in] const int & x				coordinate for drawing the texture along the X axis
	 */
	Unit(SDL_Texture *img, const int &x, const int &y);

	/**
	 * @brief								Getter which return the collision rectangle of unit
	 */
	SDL_Rect getrect() const;

	/**
	 * @brief								Method that responds to draw animation of Unit
	 *
	 * @param[in] SDL_Texture * ren			pointer to render surface
	 * @param[in] const int & frame			frame number from sprite animation
	 */
	void Draw(SDL_Renderer *ren, const int &frame) const;

	/**
	 * @brief								Method that emits Unit activity
	 *
	 * @details								Calls a method to place bomb or get bonuses, verifies that a unit has obstacles
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the object is still active and false otherwise
	 */
	virtual bool Action(Game &game);

	/**
	 * @brief								Method that responds to an attempt to destroy an object with a flame
	 *
	 * @details								Calls a method to draw an Unit death animation
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the object is possible to destroy and false otherwise
	 */
	bool tryDestroy(Game &game);

	~Unit();

protected:

	int direct, move, maxcooldown = 100, cooldown, speed, range;

};

#endif 
