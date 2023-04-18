#ifndef DESPLAYER_H
#define DESPLAYER_H

#include "Object.h"
#include "Game.h"

/**
 * @brief									The class that represents playing animation of players death - DesPlayer
 */
class DesPlayer : public Object {
public:

	/**
	 * @brief								Standard constructor initializing object
	 *
	 * @param[in] SDL_Texture * img			object texture pointer
	 * @param[in] const int & y				coordinate for drawing the texture along the Y axis
	 * @param[in] const int & x				coordinate for drawing the texture along the X axis
	 * @param[in] const int & time			time allotted for playing animation
	 */
	DesPlayer(SDL_Texture *img, const int &y, const int &x, const int &time);

	/**
	 * @brief								Method that emits playing animation
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the animation is still active and false otherwise
	 */
	bool Action(Game &game);

	/**
	 * @brief								Method that responds to draw animation of players death
	 *
	 * @param[in] SDL_Texture * ren			pointer to render surface
	 * @param[in] const int & frame			frame number from sprite animation
	 */
	void Draw(SDL_Renderer *ren, const int &frame) const;

	~DesPlayer();

private:

	int maxlifetime;
	int lifetime;

};

#endif