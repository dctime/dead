#include "DEAD_functions.h"
#include "DEAD_map.h"
#include "subrenderers/DEAD_decoration_renderer.h"
#include <DEAD_controllable_player.h>
#include <DEAD_game.h>
#include <DEAD_renderer.h>
#include <DEAD_renderer3d.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <subrenderers/DEAD_explainer.h>
#include <subrenderers/DEAD_player_inventory_renderer.h>
#include <subrenderers/DEAD_shadow_caster.h>
#include <subrenderers/DEAD_ui_renderer.h>

DEAD_Renderer3D::DEAD_Renderer3D(SDL_Window *window, DEAD_Renderer *renderer,
                                 DEAD_Game *game)
    : window(window), renderer(renderer), game(game), minimapWidth(324),
      minimapHeight(216), horizontalFOV(60), heightForHalfFullInOneMapBlock(1),
      maxRenderDistance(10), blockRenderHeight(4) {
  this->minimapTexture =
      SDL_CreateTexture(this->renderer->getSDLRenderer(),
                        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                        this->game->SCREEN_WIDTH, this->game->SCREEN_HEIGHT);
  this->playerViewLayerTexture =
      SDL_CreateTexture(this->renderer->getSDLRenderer(),
                        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                        this->game->SCREEN_WIDTH, this->game->SCREEN_HEIGHT);
}

DEAD_Renderer3D::~DEAD_Renderer3D() {
  SDL_DestroyTexture(this->minimapTexture);
  SDL_FreeFormat(format);
}

void DEAD_Renderer3D::render() {

  SDL_SetRenderTarget(this->renderer->getSDLRenderer(),
                      this->renderer->getRenderTargetTexture());
  SDL_SetRenderDrawBlendMode(this->renderer->getSDLRenderer(),
                             SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 10, 0, 10, 255);
  SDL_RenderClear(this->renderer->getSDLRenderer());

  this->renderFirstLayer();

  this->renderer->uiRenderer->render();
  this->renderer->playerInventoryRenderer->render();
  this->renderMinimap();
  this->renderer->renderYouDied();

  SDL_RenderPresent(this->renderer->getSDLRenderer());
}

void DEAD_Renderer3D::renderMinimap() {
  this->renderer->setRenderBlockSize(30);
  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), this->minimapTexture);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 0, 0, 0, 0);
  SDL_RenderClear(this->renderer->getSDLRenderer());
  this->renderer->renderTargetTexture = this->minimapTexture;

  this->renderer->moveRenderAnchor(this->game->getPlayer()->getPos().x,
                                   this->game->getPlayer()->getPos().y,
                                   (int)(this->game->SCREEN_WIDTH / 2),
                                   (int)(this->game->SCREEN_HEIGHT / 2));

  this->renderer->renderMapObjects();
  this->renderer->decorationRenderer->render();
  this->renderer->renderItemDropLayer();
  this->renderer->renderBullets();
  this->renderer->renderPlayer(this->game->getPlayer());
  this->renderer->renderZombies(this->game->getZombieDirector());
  // this->drawZombieMovementMap();
  this->renderer->shadowCaster->render();
  this->renderer->renderPlayerMemoriable();
  this->renderer->particleRenderer->render();

  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), NULL);
  SDL_Rect textureRect = {
      .x = (int)(this->game->SCREEN_WIDTH / 2 - this->minimapWidth / 2),
      .y = (int)(this->game->SCREEN_HEIGHT / 2 - this->minimapHeight / 2),
      .w = this->minimapWidth,
      .h = this->minimapHeight};

  SDL_Rect screenRect = {.x = this->game->SCREEN_WIDTH - this->minimapWidth,
                         .y = 0,
                         .w = this->minimapWidth,
                         .h = this->minimapHeight};
  SDL_RenderCopy(this->renderer->getSDLRenderer(), this->minimapTexture,
                 &textureRect, &screenRect);

  this->renderer->renderTargetTexture = nullptr;
  SDL_SetRenderTarget(this->renderer->getSDLRenderer(),
                      this->renderer->getRenderTargetTexture());
}

void DEAD_Renderer3D::renderFirstLayer() {
  void *pixels;
  int pitch;
  SDL_LockTexture(this->playerViewLayerTexture, NULL, &pixels, &pitch);

  Uint32 *pixelData = (Uint32 *)pixels;

  for (int y = 0; y < this->game->SCREEN_HEIGHT; y++) {
    for (int x = 0; x < this->game->SCREEN_WIDTH; x++) {
      pixelData[y * (pitch / 4) + x] =
          SDL_MapRGBA(format, 0, 0, 0, 255); // Set pixel color
    }
  }

  double playerFacingDegree = this->game->getPlayer()->getRotation();
  double minPlayerFacingDegree = playerFacingDegree - this->horizontalFOV / 2.0;
  double unitDegreePerX =
      this->horizontalFOV / (double)this->game->SCREEN_WIDTH;

  DEAD_Map::MapLocation playerLoc = this->game->getPlayer()->getPos();
  DEAD_Vector playerLocVector = {.x = (double)playerLoc.x,
                                 .y = (double)playerLoc.y};

  // store x by distance

  std::vector<XToDistance> xToDistanceVector;

  // render lines by x

  for (int x = 0; x < this->game->SCREEN_WIDTH; x++) {
    double tempDegree = DEAD_Functions::getDegreeFromZeroTo360(
        minPlayerFacingDegree + x * unitDegreePerX);

    // get closestIntersection and distance

    DEAD_Vector playerRayUnitVector = DEAD_Functions::calUnitVector(tempDegree);
    MapSize mapSize = this->game->getMap()->getMapSize();
    double rayLength =
        DEAD_Functions::calDistance(mapSize.width, 0, 0, mapSize.height);

    DEAD_Vector playerRayEnd = {
        .x = (double)(playerLoc.x + playerRayUnitVector.x * rayLength),
        .y = (double)(playerLoc.y + playerRayUnitVector.y * rayLength)};
    DEAD_Line playerRay = {.point1 = playerLocVector, .point2 = playerRayEnd};

    DEAD_Map::MapLocation closestIntersection;
    DEAD_Vector tempIntersection;
    double closestDistance = MAXFLOAT;

    for (const DEAD_Map::MapLine &line : this->game->getMap()->getLines()) {
      DEAD_Vector linePoint1 = {.x = (double)line.point1.x,
                                .y = (double)line.point1.y};
      DEAD_Vector linePoint2 = {.x = (double)line.point2.x,
                                .y = (double)line.point2.y};
      DEAD_Line tempLine = {.point1 = linePoint1, .point2 = linePoint2};

      if (DEAD_Functions::linesIntersection(tempLine, playerRay,
                                            tempIntersection)) {
        double tempDistance = DEAD_Functions::calDistance(
            playerLoc.x, playerLoc.y, tempIntersection.x, tempIntersection.y);
        if (tempDistance < closestDistance) {
          closestIntersection = {.x = tempIntersection.x,
                                 .y = tempIntersection.y};
          closestDistance = tempDistance;
        }
      }
    }

    XToDistance xToDistance = {.x = x, .distance = closestDistance};
    xToDistanceVector.push_back(xToDistance);
  }

  std::sort(xToDistanceVector.begin(), xToDistanceVector.end(),
            this->sortByDistance);

  for (const XToDistance &data : xToDistanceVector) {
    std::cout << data.distance << std::endl;
    double colorRatio = 0;
    if (data.distance <= this->maxRenderDistance) {
      colorRatio =
          (this->maxRenderDistance - data.distance) / this->maxRenderDistance;
    }

    double fullHalfRequiredHeight =
        this->heightForHalfFullInOneMapBlock * data.distance;

    // upper half
    double upperHalfLength = 1 - this->game->getPlayer()->getPlayerHeight();
    if (upperHalfLength > 0) {
      int renderLength = (int)((this->game->SCREEN_HEIGHT / 2.0) *
                               (upperHalfLength / fullHalfRequiredHeight) *
                               this->blockRenderHeight);
      int startY = (int)((this->game->SCREEN_HEIGHT / 2.0) - renderLength);
      if (startY < 0) {
        startY = 0;
      }

      for (int y = startY; y <= (int)(this->game->SCREEN_HEIGHT / 2.0); y++) {
        pixelData[y * (pitch / 4) + data.x] =
            SDL_MapRGBA(format, 255 * colorRatio, 255 * colorRatio,
                        255 * colorRatio, 255); // Set pixel color
      }
    }

    // lower half
    double lowerHalfLength = this->game->getPlayer()->getPlayerHeight();
    if (lowerHalfLength > 0) {
      int renderLength = (int)((this->game->SCREEN_HEIGHT / 2.0) *
                               (lowerHalfLength / fullHalfRequiredHeight) *
                               this->blockRenderHeight);

      int endY = (int)((this->game->SCREEN_HEIGHT / 2.0) + renderLength);
      if (endY >= this->game->SCREEN_HEIGHT) {
        endY = this->game->SCREEN_HEIGHT - 1;
      }

      for (int y = (int)(this->game->SCREEN_HEIGHT / 2.0); y <= endY; y++) {
        pixelData[y * (pitch / 4) + data.x] =
            SDL_MapRGBA(format, 255 * colorRatio, 255 * colorRatio,
                        255 * colorRatio, 255); // Set pixel color
      }
    }
  }

  SDL_UnlockTexture(this->playerViewLayerTexture);

  SDL_RenderCopy(this->renderer->getSDLRenderer(), this->playerViewLayerTexture,
                 NULL, NULL);
}

bool DEAD_Renderer3D::sortByDistance(const XToDistance &data1,
                                     const XToDistance &data2) {
  return data1.distance > data2.distance;
}
