#include <DEAD_collision_director.h>
#include <DEAD_game.h>
#include <DEAD_player.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_log.h>
#include <hitbox/DEAD_circle_hitbox.h>
#include <iostream>
#include <map_objects/DEAD_map_object_base.h>
#include <memory>
#include <vector>
DEAD_CollisionDirector::DEAD_CollisionDirector(std::shared_ptr<DEAD_Game> game)
    : game(game) {
  SDL_Log("collision init");
}

std::set<std::shared_ptr<DEAD_MapObjectBase>>
DEAD_CollisionDirector::entityCheckCollision(
    double targetX, double targetY,
    const std::shared_ptr<DEAD_Entity> &entity) {
  std::vector<std::vector<int>> checkSequence = {{0, 0},  {1, 0},   {-1, 0},
                                                 {0, 1},  {0, -1},  {1, 1},
                                                 {1, -1}, {-1, -1}, {-1, 1}};

  std::set<std::shared_ptr<DEAD_MapObjectBase>> collideObjects;
  collideObjects.clear();

  for (std::vector<int> v : checkSequence) {
    int objectX = v[0] + (int)(targetX);
    int objectY = v[1] + (int)(targetY);

    if (objectX < 0 || objectX >= this->game->getMap()->getMapSize().width)
      continue;
    if (objectY < 0 || objectY >= this->game->getMap()->getMapSize().height)
      continue;

  std:;
    std::shared_ptr<DEAD_MapObjectBase> object =
        this->game->getMap()->getMapObjects()[objectY][objectX];
    if (!object->isZombieCollidable()) {
      continue;
    }

    DEAD_Map::MapLocation futureLoc = {.x = targetX, .y = targetY};

    if (object->getHitBox()->isCollideWithCircle(
            futureLoc, entity->getHitbox()->getRadius())) {
      collideObjects.insert(object);
    }
  }

  return collideObjects;
}

std::set<std::shared_ptr<DEAD_MapObjectBase>>
DEAD_CollisionDirector::playerCheckCollision(
    double targetX, double targetY,
    const std::shared_ptr<DEAD_Player> &player) {
  std::vector<std::vector<int>> checkSequence = {{0, 0},  {1, 0},   {-1, 0},
                                                 {0, 1},  {0, -1},  {1, 1},
                                                 {1, -1}, {-1, -1}, {-1, 1}};

  std::set<std::shared_ptr<DEAD_MapObjectBase>> collideObjects;
  collideObjects.clear();

  for (std::vector<int> v : checkSequence) {
    int objectX = v[0] + (int)(targetX);
    int objectY = v[1] + (int)(targetY);

    if (objectX < 0 || objectX >= this->game->getMap()->getMapSize().width)
      continue;
    if (objectY < 0 || objectY >= this->game->getMap()->getMapSize().height)
      continue;

    std::shared_ptr<DEAD_MapObjectBase> object =
        this->game->getMap()->getMapObjects()[objectY][objectX];
    if (!object->isPlayerCollidable()) {
      continue;
    }

    DEAD_Map::MapLocation futureLoc = {.x = targetX, .y = targetY};

    if (object->getHitBox()->isCollideWithCircle(
            futureLoc, player->getHitbox()->getRadius())) {
      collideObjects.insert(object);
    }
  }

  return collideObjects;
}

std::set<std::shared_ptr<DEAD_MapObjectBase>>
DEAD_CollisionDirector::entityCheckCollision(
    const std::shared_ptr<DEAD_Entity> &entity,
    DEAD_Map::MapLocation targetLoc) {
  return entityCheckCollision(targetLoc.x, targetLoc.y, entity);
}

std::set<std::shared_ptr<DEAD_MapObjectBase>>
DEAD_CollisionDirector::playerCheckCollision(
    const std::shared_ptr<DEAD_Player> &player,
    DEAD_Map::MapLocation targetLoc) {
  return playerCheckCollision(targetLoc.x, targetLoc.y, player);
}

std::set<std::shared_ptr<DEAD_MapObjectBase>>
DEAD_CollisionDirector::entityCheckCollision(
    const std::shared_ptr<DEAD_Entity> &player, double moveXDelta,
    double moveYDelta) {

  DEAD_Map::MapLocation playerLoc = player->getPos();

  double targetX = player->getPos().x + moveXDelta;
  double targetY = player->getPos().y + moveYDelta;

  DEAD_Map::MapLocation futureLoc = player->getPos();
  futureLoc.x += moveXDelta;
  futureLoc.y += moveYDelta;

  return entityCheckCollision(player, futureLoc);
}

std::set<std::shared_ptr<DEAD_MapObjectBase>>
DEAD_CollisionDirector::playerCheckCollision(
    const std::shared_ptr<DEAD_Player> &player, double moveXDelta,
    double moveYDelta) {

  DEAD_Map::MapLocation playerLoc = player->getPos();

  double targetX = player->getPos().x + moveXDelta;
  double targetY = player->getPos().y + moveYDelta;

  DEAD_Map::MapLocation futureLoc = player->getPos();
  futureLoc.x += moveXDelta;
  futureLoc.y += moveYDelta;

  return playerCheckCollision(player, futureLoc);
}

std::set<std::shared_ptr<DEAD_MapObjectBase>>
DEAD_CollisionDirector::bulletCheckCollision(
    const std::shared_ptr<DEAD_Bullet> &bullet) {
  std::vector<std::vector<int>> checkSequence = {{0, 0},  {1, 0},   {-1, 0},
                                                 {0, 1},  {0, -1},  {1, 1},
                                                 {1, -1}, {-1, -1}, {-1, 1}};

  std::set<std::shared_ptr<DEAD_MapObjectBase>> collideObjects;
  collideObjects.clear();

  for (std::vector<int> v : checkSequence) {
    int objectX = v[0] + (int)(bullet->getLoc().x);
    int objectY = v[1] + (int)(bullet->getLoc().y);

    if (objectX < 0 || objectX >= this->game->getMap()->getMapSize().width)
      continue;
    if (objectY < 0 || objectY >= this->game->getMap()->getMapSize().height)
      continue;

    std::shared_ptr<DEAD_MapObjectBase> object =
        this->game->getMap()->getMapObjects()[objectY][objectX];
    if (!object->isPlayerCollidable()) {
      continue;
    }

    if (object->getHitBox()->isCollideWithCircle(bullet->getLoc(),
                                                 bullet->getBulletSize() / 2)) {
      collideObjects.insert(object);
    }
  }

  return collideObjects;
}
