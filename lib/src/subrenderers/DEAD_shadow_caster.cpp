#include "SDL_pixels.h"
#include "SDL_surface.h"
#include "labels/DEAD_label_base.h"
#include "map_objects/DEAD_map_object_base.h"
#include "subrenderers/DEAD_subrenderer_base.h"
#include <DEAD_functions.h>
#include <DEAD_game.h>
#include <DEAD_renderer.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <cstdint>
#include <labels/DEAD_point_label.h>
#include <memory>
#include <subrenderers/DEAD_shadow_caster.h>
#include <vector>

DEAD_ShadowCaster::DEAD_ShadowCaster(DEAD_Renderer *renderer)
    : DEAD_SubRendererBase(renderer), map(renderer->getGame()->getMap()),
      labelRenderer(std::make_unique<DEAD_LabelRenderer>(renderer)) {
  updateShadowCaster();
}

void DEAD_ShadowCaster::render() {

  // make a square mask

  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 255, 0, 0, 255);

  for (DEAD_Map::MapLine line : lines) {
    ScreenLocation loc1 =
        this->renderer->getPointRenderLocation(line.point1.x, line.point1.y);
    ScreenLocation loc2 =
        this->renderer->getPointRenderLocation(line.point2.x, line.point2.y);
    // SDL_RenderDrawLine(this->renderer->getSDLRenderer(), loc1.x, loc1.y,
    // loc2.x,
    //                    loc2.y);
  }

  // for (DEAD_Map::MapLocation point : points) {
  //   ScreenLocation loc = this->renderer->getPointRenderLocation(point.x,
  //   point.y); filledCircleRGBA(this->renderer->getSDLRenderer(), loc.x,
  //   loc.y, 3, 255, 0, 0, 255);
  // }

  // render data
  std::vector<double> directions;
  std::vector<DEAD_Vector> intersections;

  // get all angles
  DEAD_Map::MapLocation playerLoc =
      this->renderer->getGame()->getPlayer()->getPos();
  double deltaAngle = 0.0001;

  for (const DEAD_Map::MapLocation &point : points) {
    double angle =
        DEAD_Functions::calAngle(playerLoc.x, playerLoc.y, point.x, point.y);
    directions.push_back(angle - deltaAngle);
    directions.push_back(angle);
    directions.push_back(angle + deltaAngle);
  }

  std::sort(directions.begin(), directions.end());

  // ray it each with three lines get all intersection
  double playerDistance = DEAD_Functions::calDistance(
      0, this->map->getMapSize().width, this->map->getMapSize().height, 0);

  for (double direction : directions) {
    DEAD_Line ray;
    ray.point1 = {.x = playerLoc.x, .y = playerLoc.y};
    DEAD_Vector targetVector = DEAD_Functions::calUnitVector(direction);
    ray.point2 = {.x = playerLoc.x + targetVector.x * playerDistance,
                  .y = playerLoc.y + targetVector.y * playerDistance};

    ScreenLocation point1Loc =
        this->renderer->getPointRenderLocation(ray.point1.x, ray.point1.y);
    ScreenLocation point2Loc =
        this->renderer->getPointRenderLocation(ray.point2.x, ray.point2.y);

    // SDL_RenderDrawLine(this->renderer->getSDLRenderer(), point1Loc.x,
    // point1Loc.y, point2Loc.x, point2Loc.y);

    DEAD_Vector closestIntersection;
    double closestIntersectionDistance = MAXFLOAT;

    for (const DEAD_Map::MapLine &line : this->lines) {
      DEAD_Line boarderLine;
      boarderLine.point1.x = line.point1.x;
      boarderLine.point1.y = line.point1.y;
      boarderLine.point2.x = line.point2.x;
      boarderLine.point2.y = line.point2.y;

      DEAD_Vector tempIntersection;
      if (DEAD_Functions::linesIntersection(boarderLine, ray,
                                            tempIntersection)) {
        // std::cout << tempIntersection.x << " | " << tempIntersection.y <<
        // std::endl;
        double tempDistance = DEAD_Functions::calDistance(
            playerLoc.x, playerLoc.y, tempIntersection.x, tempIntersection.y);
        if (closestIntersectionDistance > tempDistance) {
          closestIntersection = tempIntersection;
          closestIntersectionDistance = tempDistance;
        }
      }
    }

    intersections.push_back(closestIntersection);
  }

  // test intersections
  //
  // for (const DEAD_Vector& intersection : intersections) {
  //   ScreenLocation loc =
  //   this->renderer->getPointRenderLocation(intersection.x, intersection.y);
  //   filledCircleRGBA(this->renderer->getSDLRenderer(), loc.x, loc.y, 3, 0, 0,
  //   255, 255);
  // }

  SDL_BlendMode whiteToMask = SDL_ComposeCustomBlendMode(
      SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ZERO, SDL_BLENDOPERATION_ADD,
      SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA, SDL_BLENDFACTOR_ZERO,
      SDL_BLENDOPERATION_ADD);

  SDL_Texture *shadowMask = SDL_CreateTexture(
      this->renderer->getSDLRenderer(), SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_TARGET, this->renderer->getGame()->SCREEN_WIDTH,
      this->renderer->getGame()->SCREEN_HEIGHT);

  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), shadowMask);
  ScreenLocation playerScreenLoc =
      this->renderer->getPointRenderLocation(playerLoc.x, playerLoc.y);

  DEAD_Vector indexLoc;
  DEAD_Vector nextIndexLoc;

  ScreenLocation indexScreenLoc;
  ScreenLocation nextIndexScreenLoc;


  for (int index = 0; index < intersections.size(); index++) {

    int nextIndex = index + 1;
    if (nextIndex == intersections.size()) {
      nextIndex = 0;
    }

    indexLoc = intersections.at(index);
    nextIndexLoc = intersections.at(nextIndex);

    indexScreenLoc =
        this->renderer->getPointRenderLocation(indexLoc.x, indexLoc.y);
    nextIndexScreenLoc =
        this->renderer->getPointRenderLocation(nextIndexLoc.x, nextIndexLoc.y);

    SDL_Vertex vertex_1 = {{(float)indexScreenLoc.x, (float)indexScreenLoc.y},
                           {255, 255, 255, 255},
                           {1, 1}};
    SDL_Vertex vertex_2 = {{(float)playerScreenLoc.x, (float)playerScreenLoc.y},
                           {255, 255, 255, 255},
                           {1, 1}};
    SDL_Vertex vertex_3 = {
        {(float)nextIndexScreenLoc.x, (float)nextIndexScreenLoc.y},
        {255, 255, 255, 255},
        {1, 1}};

    SDL_Vertex vertices[] = {vertex_1, vertex_2, vertex_3};

    SDL_Texture *texture;
    // only alpha matters, color doesnt matter
    SDL_RenderGeometry(this->renderer->getSDLRenderer(), texture, vertices, 3,
                       NULL, 0);
    SDL_DestroyTexture(texture);
  }

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

  SDL_RenderCopy(this->renderer->getSDLRenderer(), shadowMask, NULL, NULL);
}

void DEAD_ShadowCaster::updateShadowCaster() {
  this->lines.clear();
  this->points.clear();
  LocLineStatus locLineStatus(this->map);

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
              locLineStatus.getLineStatus(x, y - 1, this->map).rightLineIndex;
          if (rightLineIndex != -1) {
            lines.at(rightLineIndex).point2 = {.x = (double)(x + 1),
                                               .y = (double)(y + 1)};
            locLineStatus.setLineStatus(x, y).rightLineIndex = rightLineIndex;
          } else {
            int index = lines.size();
            DEAD_Map::MapLine line = {
                .point1 = {.x = (double)x + 1, .y = (double)y},
                .point2 = {.x = (double)x + 1, .y = (double)(y + 1)}};
            lines.push_back(line);
            locLineStatus.setLineStatus(x, y).rightLineIndex = index;
          }
        } else {
          int index = lines.size();
          DEAD_Map::MapLine line = {
              .point1 = {.x = (double)x + 1, .y = (double)y},
              .point2 = {.x = (double)x + 1, .y = (double)(y + 1)}};
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
              locLineStatus.getLineStatus(x - 1, y, this->map).upLineIndex;
          if (upLineIndex != -1) {
            lines.at(upLineIndex).point2 = {.x = (double)(x + 1),
                                            .y = (double)(y)};
            locLineStatus.setLineStatus(x, y).upLineIndex = upLineIndex;
          } else {
            int index = lines.size();
            DEAD_Map::MapLine line = {
                .point1 = {.x = (double)x, .y = (double)y},
                .point2 = {.x = (double)x + 1, .y = (double)(y)}};
            lines.push_back(line);
            locLineStatus.setLineStatus(x, y).upLineIndex = index;
          }
        } else {
          int index = lines.size();
          DEAD_Map::MapLine line = {
              .point1 = {.x = (double)x, .y = (double)y},
              .point2 = {.x = (double)x + 1, .y = (double)(y)}};
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
              locLineStatus.getLineStatus(x - 1, y, this->map).downLineIndex;
          if (downLineIndex != -1) {
            lines.at(downLineIndex).point2 = {.x = (double)(x + 1),
                                              .y = (double)(y + 1)};
            locLineStatus.setLineStatus(x, y).downLineIndex = downLineIndex;
          } else {
            int index = lines.size();
            DEAD_Map::MapLine line = {
                .point1 = {.x = (double)x, .y = (double)y + 1},
                .point2 = {.x = (double)x + 1, .y = (double)(y + 1)}};
            lines.push_back(line);
            locLineStatus.setLineStatus(x, y).downLineIndex = index;
          }
        } else {
          int index = lines.size();
          DEAD_Map::MapLine line = {
              .point1 = {.x = (double)x, .y = (double)y + 1},
              .point2 = {.x = (double)x + 1, .y = (double)(y + 1)}};
          lines.push_back(line);
          locLineStatus.setLineStatus(x, y).downLineIndex = index;
        }
      }
    }
  }

  for (DEAD_Map::MapLine line : lines) {
    points.insert(line.point1);
    points.insert(line.point2);
  }

  int mapPoints[][2] = {
      {0, 0},
      {0, this->map->getMapSize().height},
      {this->map->getMapSize().width, 0},
      {this->map->getMapSize().width, this->map->getMapSize().height}};

  for (int element = 0; element < 4; element++) {
    DEAD_Map::MapLocation loc = {.x = (double)mapPoints[element][0],
                                 .y = (double)mapPoints[element][1]};
    points.insert(loc);
  }
}
