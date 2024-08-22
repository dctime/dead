#pragma once

#include "../DEAD_player.h"
#include "../items/weapons/guns/DEAD_gun.h"
#include <SDL2/SDL.h>
#include <memory>

/*This is a C++ class definition for a "dead bullet" object in a game. Here's a summary of the class:

* The class has several member functions:
	+ A constructor that takes three parameters: an owner player, a gun, and a speed.
	+ Several getter methods to retrieve information about the bullet:
		- Owner player
		- Gun used to fire the bullet
		- Bullet size
		- Map location (x, y)
		- Rotation angle
	* Setter method for map location (x, y)
	* Methods to move and update the bullet's position and rotation
	+ `tickFly()`: moves the bullet
	+ `tickBullet()`: updates the bullet's position and rotation
* The class has several pure virtual functions that must be implemented by any derived classes:
	+ `getBulletTextureRect()`: returns a rectangle representing the bullet's texture
	+ `getBulletSize()`: returns the size of the bullet
	+ `registerBullet()`: registers the bullet in some way (e.g., with the game's physics engine)
	+ `tickBullet()`: updates the bullet's position and rotation
* The class has a private member variable for each of the above-mentioned properties.

Note that this is an abstract base class, meaning it cannot be instantiated on its own and must be inherited by derived classes to provide implementation for the pure virtual functions.
*/

class DEAD_Bullet : public std::enable_shared_from_this<DEAD_Bullet> {
public:
  DEAD_Bullet(DEAD_Player* owner, DEAD_Gun* gun, double speed, int damage);
  virtual SDL_Rect getBulletTextureRect() = 0;
  DEAD_Player* getOwner();
  virtual double getBulletSize() = 0;
  DEAD_Map::MapLocation getMapLocation();
  DEAD_Gun* getGun();
  double getRotation();
  DEAD_Map::MapLocation getLoc();
  void setLoc(DEAD_Map::MapLocation loc);
  void move(double x, double y);
  void tickFly();
  virtual void tickBullet() = 0;
  virtual ~DEAD_Bullet();
  DEAD_CircleHitbox* getHitBox();
  int getDamage();
private:
  DEAD_Player* owner;
  DEAD_Map::MapLocation pos;
  DEAD_Gun* gun;
  DEAD_Game* game;
  double rotation;
  double speed;
  int damage;
  std::unique_ptr<DEAD_CircleHitbox> hitbox;
};
