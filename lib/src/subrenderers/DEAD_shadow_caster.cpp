#include "SDL_mouse.h"
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
  this->shadowMask = SDL_CreateTexture(
      this->renderer->getSDLRenderer(), SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_TARGET, this->renderer->getGame()->SCREEN_WIDTH,
      this->renderer->getGame()->SCREEN_HEIGHT);
  this->shadowOutwardMask = SDL_CreateTexture(
      this->renderer->getSDLRenderer(), SDL_PIXELFORMAT_RGBA8888,
      SDL_TEXTUREACCESS_TARGET, this->renderer->getGame()->SCREEN_WIDTH,
      this->renderer->getGame()->SCREEN_HEIGHT);
}

bool DEAD_ShadowCaster::isMouseInLineOfSight() {
  // always updated when rendering
  return this->mouseInLineOfSight;
}

void DEAD_ShadowCaster::render() {
  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), this->renderer->getRenderTargetTexture());
  this->mouseInLineOfSight = false;

  // make a square mask

  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 255, 0, 0, 255);

  for (DEAD_Map::MapLine line : this->map->getLines()) {
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

  // get all angles
  DEAD_Map::MapLocation playerLoc =
      this->renderer->getGame()->getPlayer()->getPos();
  double deltaAngle = 0.0001;

  for (const DEAD_Map::MapLocation &point : this->map->getPoints()) {
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
  std::vector<DEAD_Vector> intersections;

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
    //                    point1Loc.y, point2Loc.x, point2Loc.y);

    DEAD_Vector closestIntersection;
    double closestIntersectionDistance = MAXFLOAT;

    for (const DEAD_Map::MapLine &line : this->map->getLines()) {
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

  // for (const DEAD_Vector &intersection : intersections) {
  //   ScreenLocation loc =
  //       this->renderer->getPointRenderLocation(intersection.x,
  //       intersection.y);
  //   SDL_Rect rect = {.x = loc.x - 5, .y = loc.y - 5, .w = 10, .h = 10};
  //   SDL_RenderFillRect(this->renderer->getSDLRenderer(), &rect);
  // }

  SDL_BlendMode whiteToMask = SDL_ComposeCustomBlendMode(
      SDL_BLENDFACTOR_ONE, SDL_BLENDFACTOR_ZERO, SDL_BLENDOPERATION_ADD,
      SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA, SDL_BLENDFACTOR_ZERO,
      SDL_BLENDOPERATION_ADD);

  ScreenLocation playerScreenLoc =
      this->renderer->getPointRenderLocation(playerLoc.x, playerLoc.y);

  // /* ============ inner mask render ================ */

  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), this->shadowMask);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 0, 0, 0, 0);
  SDL_RenderClear(this->renderer->getSDLRenderer());

  for (int index = 0; index < intersections.size(); index++) {
    DEAD_Vector indexLoc;
    DEAD_Vector nextIndexLoc;

    ScreenLocation indexScreenLoc;
    ScreenLocation nextIndexScreenLoc;

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

    DEAD_Triangle triangle;
    triangle.point1 = {.x = (double)indexScreenLoc.x,
                       .y = (double)indexScreenLoc.y};
    triangle.point2 = {.x = (double)playerScreenLoc.x,
                       .y = (double)playerScreenLoc.y};
    triangle.point3 = {.x = (double)nextIndexScreenLoc.x,
                       .y = (double)nextIndexScreenLoc.y};

    ScreenLocation mouseLoc;
    SDL_GetMouseState(&mouseLoc.x, &mouseLoc.y);
    DEAD_Vector mouseLocVector = {.x = (double)mouseLoc.x,
                                  .y = (double)mouseLoc.y};
    PointAndTriangleReturn pointAndTriangleReturn =
        DEAD_Functions::checkPointAndTriangle(mouseLocVector, triangle);

    SDL_Vertex vertices[] = {vertex_1, vertex_2, vertex_3};

    // only alpha matters, color doesnt matter
    SDL_RenderGeometry(this->renderer->getSDLRenderer(), NULL, vertices, 3,
                       NULL, 0);
    if (pointAndTriangleReturn == POINT_IN_TRIANGLE ||
        pointAndTriangleReturn == POINT_ON_TRIANGLE) {
      this->mouseInLineOfSight = true;
    }
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

  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), this->renderer->getRenderTargetTexture());
  SDL_SetTextureBlendMode(this->shadowMask, SDL_BLENDMODE_BLEND);

  SDL_RenderCopy(this->renderer->getSDLRenderer(), this->shadowMask, NULL,
                 NULL);
}


