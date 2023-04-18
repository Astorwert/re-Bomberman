#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <cstdlib>  
#include "SDL2\include\SDL.h"
#include "SDL2\include\SDL_image.h"
#include <list>
#include <vector>
#include "Texture.h"


using namespace std;

class Game;

/**
 * @brief									The class that represents the parent class of all game objects - Object
 */
class Object {
public:


	/**
	 * @brief								Standard constructor initializing new Object
	 *
	 * @param[in] SDL_Texture * img			object texture pointer
	 * @param[in] const int & y				coordinate for drawing the texture along the Y axis
	 * @param[in] const int & x				coordinate for drawing the texture along the X axis
	 */
	Object(SDL_Texture *img,const int &y, const int &x);

	/**
	 * @brief								basic method to render object
	 *
	 * @param[in] SDL_Texture * ren			pointer to render surface
	 * @param[in] const int & frame			frame number from sprite animation
	 */
	virtual void Draw(SDL_Renderer *ren,const int &frame) const;

	/**
	 * @brief								Method that emits Object activity
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the object is still alive and false otherwise
	 */
	virtual bool Action(Game &game);

	/**
	 * @brief								Method that responds to an attempt to destroy an object with a flame
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true if the object is possible to destroy and false otherwise
	 */
	virtual bool tryDestroy(Game &game);

	/**
	 * @brief								Method that responds to an attempt to collect an object by player or AI
	 *
	 * @param[in] Game & game				reference to game class object
	 *
	 * @return								true number of bonus type
	 */
	virtual int tryCollect(Game &game);

	/**
	 * @brief								Getter which return char symbol of object
	 */
	virtual char getchar() const;

	/**
	 * @brief								Getter which return the collision rectangle of object
	 */
	virtual SDL_Rect getrect() const;

	/**
	 * @brief								returns the ability of an object to stop a flame 
	 */
	bool catchFlame() const;

	/**
	 * @brief								returns the ability of an object to be an obstacle
	 */
	bool getcol() const;

	virtual ~Object();

protected:

	SDL_Texture *tileset;
	int h, w;
	int x, y;
	bool col = false;
	bool prevent;
	char symb = '.';

};

#endif
