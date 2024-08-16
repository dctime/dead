#include "SDL_pixels.h"
#include "SDL_surface.h"
#include "labels/DEAD_label_base.h"
#include "map_objects/DEAD_map_object_base.h"
#include "subrenderers/DEAD_subrenderer_base.h"
#include <DEAD_game.h>
#include <DEAD_renderer.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_render.h>
#include <SDL2_gfxPrimitives.h>
#include <cstdint>
#include <labels/DEAD_point_label.h>
#include <memory>
#include <subrenderers/DEAD_shadow_caster.h>
#include <vector>

DEAD_ShadowCaster::DEAD_ShadowCaster(DEAD_Renderer *renderer)
    : DEAD_SubRendererBase(renderer), map(renderer->getGame()->getMap()),
      labelRenderer(std::make_unique<DEAD_LabelRenderer>(renderer)) {}

void DEAD_ShadowCaster::render() {
  ScreenLocation testLoc = this->renderer->getPointRenderLocation(1, 1);
  std::unique_ptr<DEAD_LabelBase> testPoint =
      std::make_unique<DEAD_PointLabel>(3, 28, 0.3, this->renderer);
  this->labelRenderer->addLabel(testPoint);
  this->labelRenderer->render();
  // make a square mask

  SDL_BlendMode whiteToMask = SDL_ComposeCustomBlendMode(
      SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ZERO, SDL_BLENDOPERATION_ADD,
      SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA, SDL_BLENDFACTOR_ZERO,
      SDL_BLENDOPERATION_ADD);

  SDL_Texture *shadowMask = SDL_CreateTexture(
      this->renderer->getSDLRenderer(), SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_TARGET, this->renderer->getGame()->SCREEN_WIDTH,
      this->renderer->getGame()->SCREEN_HEIGHT);

  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), shadowMask);
  Sint16 polygonX[] = {300, 500, 600, 300};
  Sint16 polygonY[] = {300, 300, 600, 800};

  // only alpha matters color doesnt matter
  filledPolygonRGBA(this->renderer->getSDLRenderer(), polygonX, polygonY, 4,
                    255, 255, 255, 255);

  // draw full screen black with mask blendmode
  SDL_SetRenderDrawBlendMode(this->renderer->getSDLRenderer(), whiteToMask);

  // r,g,b => mask color a=>shadow strength
  int shadowStrength = 255;
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 0, 0, 0,
                         shadowStrength);
  SDL_RenderFillRect(this->renderer->getSDLRenderer(), NULL);
  SDL_SetRenderDrawBlendMode(this->renderer->getSDLRenderer(),
                             SDL_BLENDMODE_BLEND);

  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), NULL);
  SDL_SetTextureBlendMode(shadowMask, SDL_BLENDMODE_BLEND);

  // SDL_RenderCopy(this->renderer->getSDLRenderer(), shadowMask, NULL, NULL);

  struct LineStatus {
    int leftLineIndex = -1;
    int rightLineIndex = -1;
    int upLineIndex = -1;
    int downLineIndex = -1;
  };

  class LocLineStatus {
  public:
    LocLineStatus(DEAD_Map *map) {
      for (int y = 0; y < map->getMapSize().height; y++) {
        std::vector<LineStatus> temp;
        for (int x = 0; x < map->getMapSize().width; x++) {
          LineStatus status;
          temp.push_back(status);
        }
        lineStatus.push_back(temp);
      }
    }

    LineStatus getLineStatus(int x, int y, DEAD_Map *map) {
      if ((x < 0 || x >= map->getMapSize().width) || y < 0 ||
          y >= map->getMapSize().height) {
        LineStatus status;
        return status;
      }

      return lineStatus.at(y).at(x);
    }

    LineStatus &setLineStatus(int x, int y) { return lineStatus.at(y).at(x); }

  private:
    std::vector<std::vector<LineStatus>> lineStatus;
  };

  LocLineStatus locLineStatus(this->map);
  std::vector<DEAD_Map::MapLine> lines;

  for (int y = 0; y < this->map->getMapSize().height; y++) {
    for (int x = 0; x < this->map->getMapSize().width; x++) {
      DEAD_MapObjectBase *object = this->map->getMapObject(x, y);
      if (!object->isZombieCollidable()) {
        continue;
      }
      // check left
      DEAD_MapObjectBase *leftObject = this->map->getMapObject(x - 1, y);
      DEAD_MapObjectBase *upObject = this->map->getMapObject(x, y - 1);
      DEAD_MapObjectBase *rightObject = this->map->getMapObject(x + 1, y);
      DEAD_MapObjectBase *downObject = this->map->getMapObject(x, y + 1);
      DEAD_MapObjectBase *leftUpObject = this->map->getMapObject(x - 1, y - 1);
      DEAD_MapObjectBase *leftDownObject =
          this->map->getMapObject(x - 1, y + 1);
      DEAD_MapObjectBase *rightUpObject = this->map->getMapObject(x + 1, y - 1);
      DEAD_MapObjectBase *rightDownObject =
          this->map->getMapObject(x + 1, y + 1);

      // check left side
      // check if solid target
      if (leftObject != nullptr && leftObject->isZombieCollidable()) {
        // do nothing
      } else {
        // check if there a already drawn target
        if (upObject != nullptr && upObject->isZombieCollidable()) {
          int leftLineIndex =
              locLineStatus.getLineStatus(x, y - 1, this->map).leftLineIndex;
          if (leftLineIndex != -1) {
            lines.at(leftLineIndex).point2 = {.x = (double)(x),
                                              .y = (double)(y + 1)};
            locLineStatus.setLineStatus(x, y).leftLineIndex = leftLineIndex;
          } else {
            int index = lines.size();
            DEAD_Map::MapLine line = {
                .point1 = {.x = (double)x, .y = (double)y},
                .point2 = {.x = (double)x, .y = (double)(y + 1)}};
            lines.push_back(line);
            locLineStatus.setLineStatus(x, y).leftLineIndex = index;
          }
        } else {
          int index = lines.size();
          DEAD_Map::MapLine line = {
              .point1 = {.x = (double)x, .y = (double)y},
              .point2 = {.x = (double)x, .y = (double)(y + 1)}};
          lines.push_back(line);
          locLineStatus.setLineStatus(x, y).leftLineIndex = index;
        }
      }

      // check right side
      // check if solid target
      if (rightObject != nullptr && rightObject->isZombieCollidable()) {
        // do nothing
      } else {
        // check if there a already drawn target
        if (upObject != nullptr && upObject->isZombieCollidable()) {
          int rightLineIndex =
              locLineStatus.getLineStatus(x, y-1, this->map).rightLineIndex;
          if (rightLineIndex != -1) {
            lines.at(rightLineIndex).point2 = {.x = (double)(x+1),
                                              .y = (double)(y + 1)};
            locLineStatus.setLineStatus(x, y).rightLineIndex = rightLineIndex;
          } else {
            int index = lines.size();
            DEAD_Map::MapLine line = {
                .point1 = {.x = (double)x+1, .y = (double)y},
                .point2 = {.x = (double)x+1, .y = (double)(y + 1)}};
            lines.push_back(line);
            locLineStatus.setLineStatus(x, y).rightLineIndex = index;
          }
        } else {
          int index = lines.size();
          DEAD_Map::MapLine line = {
              .point1 = {.x = (double)x+1, .y = (double)y},
              .point2 = {.x = (double)x+1, .y = (double)(y + 1)}};
          lines.push_back(line);
          locLineStatus.setLineStatus(x, y).rightLineIndex = index;
        }
      }

      // check up side
      // check if solid target
      if (upObject != nullptr && upObject->isZombieCollidable()) {
        // do nothing
      } else {
        // check if there a already drawn target
        if (leftObject != nullptr && leftObject->isZombieCollidable()) {
          int upLineIndex =
              locLineStatus.getLineStatus(x-1, y, this->map).upLineIndex;
          if (upLineIndex != -1) {
            lines.at(upLineIndex).point2 = {.x = (double)(x+1),
                                              .y = (double)(y)};
            locLineStatus.setLineStatus(x, y).upLineIndex = upLineIndex;
          } else {
            int index = lines.size();
            DEAD_Map::MapLine line = {
                .point1 = {.x = (double)x, .y = (double)y},
                .point2 = {.x = (double)x+1, .y = (double)(y)}};
            lines.push_back(line);
            locLineStatus.setLineStatus(x, y).upLineIndex = index;
          }
        } else {
          int index = lines.size();
          DEAD_Map::MapLine line = {
              .point1 = {.x = (double)x, .y = (double)y},
              .point2 = {.x = (double)x+1, .y = (double)(y)}};
          lines.push_back(line);
          locLineStatus.setLineStatus(x, y).upLineIndex = index;
        }
      }

      // check down side
      // check if solid target
      if (downObject != nullptr && downObject->isZombieCollidable()) {
        // do nothing
      } else {
        // check if there a already drawn target
        if (leftObject != nullptr && leftObject->isZombieCollidable()) {
          int downLineIndex =
              locLineStatus.getLineStatus(x-1, y, this->map).downLineIndex;
          if (downLineIndex != -1) {
            lines.at(downLineIndex).point2 = {.x = (double)(x+1),
                                              .y = (double)(y+1)};
            locLineStatus.setLineStatus(x, y).downLineIndex = downLineIndex;
          } else {
            int index = lines.size();
            DEAD_Map::MapLine line = {
                .point1 = {.x = (double)x, .y = (double)y+1},
                .point2 = {.x = (double)x+1, .y = (double)(y+1)}};
            lines.push_back(line);
            locLineStatus.setLineStatus(x, y).downLineIndex = index;
          }
        } else {
          int index = lines.size();
          DEAD_Map::MapLine line = {
              .point1 = {.x = (double)x, .y = (double)y+1},
              .point2 = {.x = (double)x+1, .y = (double)(y+1)}};
          lines.push_back(line);
          locLineStatus.setLineStatus(x, y).downLineIndex = index;
        }
      }

    }
  }

  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 255, 0, 0, 255);
  for (DEAD_Map::MapLine line : lines) {
    ScreenLocation loc1 = this->renderer->getPointRenderLocation(
        line.point1.x, line.point1.y);
    ScreenLocation loc2 = this->renderer->getPointRenderLocation(
        line.point2.x, line.point2.y);
    SDL_RenderDrawLine(this->renderer->getSDLRenderer(), loc1.x, loc1.y,
                       loc2.x, loc2.y);
  }

      // find all points sorted in angle
      // find all edges
      // find a way to render a polygon mask
      // complete all stuff
}
