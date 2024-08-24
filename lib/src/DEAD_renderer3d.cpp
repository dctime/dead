#include "DEAD_functions.h"
#include "DEAD_map.h"
#include "subrenderers/DEAD_decoration_renderer.h"
#include <DEAD_controllable_player.h>
#include <DEAD_game.h>
#include <DEAD_renderer.h>
#include <DEAD_renderer3d.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <subrenderers/DEAD_explainer.h>
#include <subrenderers/DEAD_player_inventory_renderer.h>
#include <subrenderers/DEAD_shadow_caster.h>
#include <subrenderers/DEAD_ui_renderer.h>

DEAD_Renderer3D::DEAD_Renderer3D(SDL_Window *window, DEAD_Renderer *renderer,
                                 DEAD_Game *game)
    : window(window), renderer(renderer), game(game), minimapWidth(324),
      minimapHeight(216), horizontalFOV(60), heightForHalfFullInOneMapBlock(0.5),
      maxRenderDistance(10) {
  this->minimapTexture =
      SDL_CreateTexture(this->renderer->getSDLRenderer(),
                        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
                        this->game->SCREEN_WIDTH, this->game->SCREEN_HEIGHT);
}

DEAD_Renderer3D::~DEAD_Renderer3D() {
  SDL_DestroyTexture(this->minimapTexture);
}

void DEAD_Renderer3D::render() {
  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), this->renderer->getRenderTargetTexture());
  SDL_SetRenderDrawBlendMode(this->renderer->getSDLRenderer(),
                             SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 10, 0, 10, 255);
  SDL_RenderClear(this->renderer->getSDLRenderer());

  double playerFacingDegree = this->game->getPlayer()->getRotation();
  double minPlayerFacingDegree = playerFacingDegree - this->horizontalFOV/2.0;
  double unitDegreePerX = this->horizontalFOV/(double)this->game->SCREEN_WIDTH;
  

  DEAD_Map::MapLocation playerLoc = this->game->getPlayer()->getPos();
  DEAD_Vector playerLocVector = {.x=(double)playerLoc.x, .y=(double)playerLoc.y};

  // render lines by x

  for (int x = 0; x < this->game->SCREEN_WIDTH; x++) {
    double tempDegree = DEAD_Functions::getDegreeFromZeroTo360(minPlayerFacingDegree + x*unitDegreePerX);

    // get closestIntersection and distance

    DEAD_Vector playerRayUnitVector = DEAD_Functions::calUnitVector(tempDegree);
    MapSize mapSize = this->game->getMap()->getMapSize();
    double rayLength = DEAD_Functions::calDistance(mapSize.width, 0, 0, mapSize.height);

    DEAD_Vector playerRayEnd = {.x=(double)(playerLoc.x+playerRayUnitVector.x*rayLength), .y=(double)(playerLoc.y+playerRayUnitVector.y*rayLength)};
    DEAD_Line playerRay = {.point1=playerLocVector, .point2=playerRayEnd};

    DEAD_Map::MapLocation closestIntersection;
    DEAD_Vector tempIntersection;
    double closestDistance = MAXFLOAT;
    for (const DEAD_Map::MapLine& line : this->game->getMap()->getLines()) {
      DEAD_Vector linePoint1 = {.x=(double)line.point1.x, .y=(double)line.point1.y};
      DEAD_Vector linePoint2 = {.x=(double)line.point2.x, .y=(double)line.point2.y};
      DEAD_Line tempLine = {.point1=linePoint1, .point2=linePoint2};

      if (DEAD_Functions::linesIntersection(tempLine, playerRay, tempIntersection)) {
        double tempDistance = DEAD_Functions::calDistance(playerLoc.x, playerLoc.y, tempIntersection.x, tempIntersection.y);
        if (tempDistance < closestDistance) {
          closestIntersection = {.x=tempIntersection.x, .y=tempIntersection.y};
          closestDistance = tempDistance;
        }
      }
    }
    

    double colorRatio = 0;
    if (closestDistance <= this->maxRenderDistance) {
      colorRatio = (this->maxRenderDistance - closestDistance) / this->maxRenderDistance;
    }

    SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 255*colorRatio, 255*colorRatio, 255*colorRatio, 255);

    double fullHalfRequiredHeight = this->heightForHalfFullInOneMapBlock * closestDistance;
    
    // upper half
    double upperHalfLength = 1 - this->game->getPlayer()->getPlayerHeight();
    if (upperHalfLength > 0) {
      int renderLength = (int)((this->game->SCREEN_HEIGHT/2.0) * (upperHalfLength/fullHalfRequiredHeight));
      SDL_RenderDrawLine(this->renderer->getSDLRenderer(), x, (int)(this->game->SCREEN_HEIGHT/2.0), x, (int)((this->game->SCREEN_HEIGHT/2.0)-renderLength));
    }

    //lower half
    double lowerHalfLength = this->game->getPlayer()->getPlayerHeight();
    if (lowerHalfLength > 0) {
      int renderLength = (int)((this->game->SCREEN_HEIGHT/2.0) * (lowerHalfLength/fullHalfRequiredHeight));
      SDL_RenderDrawLine(this->renderer->getSDLRenderer(), x, (int)(this->game->SCREEN_HEIGHT/2.0), x, (int)((this->game->SCREEN_HEIGHT/2.0)+renderLength));
    }

    
  }


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
  SDL_Rect textureRect = {.x=(int)(this->game->SCREEN_WIDTH/2-this->minimapWidth/2),
                          .y=(int)(this->game->SCREEN_HEIGHT/2-this->minimapHeight/2),
                          .w=this->minimapWidth,
                          .h=this->minimapHeight};

  SDL_Rect screenRect = {.x = this->game->SCREEN_WIDTH - this->minimapWidth,
                         .y = 0,
                         .w = this->minimapWidth,
                         .h = this->minimapHeight};
  SDL_RenderCopy(this->renderer->getSDLRenderer(), this->minimapTexture, &textureRect,
                 &screenRect);

  this->renderer->renderTargetTexture = nullptr;
  SDL_SetRenderTarget(this->renderer->getSDLRenderer(), this->renderer->getRenderTargetTexture());

}
