#include <SDL2/SDL_rect.h>
#include <map_objects/DEAD_map_object_base.h>
#include <DEAD_map.h>
#include <hitbox/DEAD_rect_hitbox.h>
#include <memory>

DEAD_MapObjectBase::DEAD_MapObjectBase(DEAD_Map::MapLocation loc) : 
  leftUpLoc(loc), hitbox(std::make_unique<DEAD_RectHitbox>(this->leftUpLoc, 1.0, 1.0)) {
};

DEAD_MapObjectBase::~DEAD_MapObjectBase() {
}

DEAD_Map::MapLocation DEAD_MapObjectBase::getLeftUpLoc() { return this->leftUpLoc; }
DEAD_RectHitbox* DEAD_MapObjectBase::getHitBox() { return this->hitbox.get(); }
SDL_Rect DEAD_MapObjectBase::getTextureRect() { return {.x=0, .y=0, .w=0, .h=0}; }

