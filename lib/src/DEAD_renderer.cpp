#include "DEAD_item_drop.h"
#include "DEAD_zombie_director.h"
#include "map_objects/DEAD_map_object_base.h"
#include "zombies/DEAD_zombie.h"
#include <DEAD_filepaths.h>
#include <DEAD_game.h>
#include <DEAD_map.h>
#include <DEAD_player.h>
#include <DEAD_renderer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <map_objects/DEAD_multitexture_object_base.h>
#include <memory>
#include <set>
#include <string>
#include <subrenderers/DEAD_decoration_renderer.h>
#include <subrenderers/DEAD_player_inventory_renderer.h>
#include <subrenderers/DEAD_ui_renderer.h>
#include <vector>

void DEAD_Renderer::getTextureFromSurface(SDL_Texture *&texture,
                                          std::string filePath) {
  SDL_Surface *textureSurface = IMG_Load(filePath.c_str());
  texture = SDL_CreateTextureFromSurface(this->renderer, textureSurface);
  SDL_FreeSurface(textureSurface);
}

void DEAD_Renderer::getTextureFromFont(std::string fontFilePath,
                                       SDL_Texture *&texture, std::string text,
                                       int fontSize, SDL_Color color) {
  TTF_Font *font = TTF_OpenFont(fontFilePath.c_str(), fontSize);
  SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
  texture = SDL_CreateTextureFromSurface(this->renderer, surface);
  SDL_FreeSurface(surface);
  TTF_CloseFont(font);
}

DEAD_Renderer::DEAD_Renderer(SDL_Window *window, DEAD_Game *game)
    : renderBlockSize(50), renderAnchor({.x = 0, .y = 0}), youDiedAlpha(0),
      playingYouDied(false), startYouDiedTicks(0) {

  if (window == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "[Renderer] Window is null");
  }

  this->renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
  if (this->renderer == NULL) {
    SDL_LogError(SDL_LOG_CATEGORY_RENDER, "[Renderer] %s", SDL_GetError());
  }

  getTextureFromSurface(this->itemTexture, DEAD_FilePaths::ITEM_TEXTURE_PNG);
  getTextureFromSurface(this->mapObjectTexture,
                        DEAD_FilePaths::MAP_OBJECT_PNG_FILE_PATH);
  getTextureFromSurface(this->playerTexture,
                        DEAD_FilePaths::PLAYER_TEXTURE_PNG);
  getTextureFromSurface(this->bulletTexture,
                        DEAD_FilePaths::BULLET_TEXTURE_PNG);
  getTextureFromSurface(this->zombiesTexture,
                        DEAD_FilePaths::ZOMBIES_TEXTURE_PNG);
  SDL_Color color = {200, 0, 0, 255};
  getTextureFromFont(DEAD_FilePaths::YOU_DIED_FONT, this->youDiedFontTexture,
                     "You Died", 72, color);
  this->game = game;
}

void DEAD_Renderer::initWithSharedFromThis(DEAD_Renderer *renderer) {
  this->uiRenderer = std::make_unique<DEAD_UIRenderer>(renderer);
  this->particleRenderer = std::make_unique<DEAD_ParticleRenderer>(renderer);
  this->playerInventoryRenderer =
      std::make_unique<DEAD_PlayerInventoryRenderer>(renderer,
                                                     this->itemTexture);
  this->decorationRenderer = std::make_unique<DEAD_DecorationRenderer>(
      renderer, this->game->getDecorationLayer());
}

DEAD_Renderer::~DEAD_Renderer() {
  SDL_DestroyTexture(this->zombiesTexture);
  SDL_DestroyTexture(this->bulletTexture);
  SDL_DestroyTexture(this->itemTexture);
  SDL_DestroyTexture(this->playerTexture);
  SDL_DestroyTexture(this->mapObjectTexture);
  SDL_DestroyRenderer(this->renderer);
}

void DEAD_Renderer::render() {

  SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(this->renderer, 10, 0, 10, 255);
  SDL_RenderClear(this->renderer);

  this->renderMapObjects();
  this->decorationRenderer->render();
  this->renderItemDropLayer();
  this->renderBullets();
  this->renderPlayer(this->game->getPlayer());
  this->renderZombies(this->game->getZombieDirector());
  // this->drawZombieMovementMap();
  this->particleRenderer->render();
  this->uiRenderer->render();
  this->playerInventoryRenderer->render();
  this->renderYouDied();

  SDL_RenderPresent(this->renderer);
}

SDL_Renderer *DEAD_Renderer::getSDLRenderer() { return this->renderer; }

DEAD_Game *DEAD_Renderer::getGame() { return this->game; }

int DEAD_Renderer::getRenderBlockSize() { return this->renderBlockSize; }

DEAD_ParticleRenderer *DEAD_Renderer::getParticleRenderer() {
  return this->particleRenderer.get();
}

void DEAD_Renderer::renderMapObjects() {
  DEAD_Map *map = this->game->getMap();

  float windowWidthMid = this->game->SCREEN_WIDTH / 2.0;
  float windowHeightMid = this->game->SCREEN_HEIGHT / 2.0;

  std::vector<std::vector<std::unique_ptr<DEAD_MapObjectBase>>> &mapObjects =
      map->getMapObjects();

  for (int i = 0; i < mapObjects.size(); ++i) {
    this->renderRect.y =
        (i - this->renderAnchor.y) * this->renderBlockSize + windowHeightMid;
    for (int j = 0; j < mapObjects[i].size(); ++j) {
      // default angle is 0
      int angle = 0;

      // Get Angle
      DEAD_MultitextureObjectBase *mapObjectMultiTexture =
          dynamic_cast<DEAD_MultitextureObjectBase *>(mapObjects[i][j].get());
      if (mapObjectMultiTexture != nullptr) {
        switch (mapObjectMultiTexture->getDirection()) {
        case DEAD_MapObjectDirection::HORIZONTAL:
          angle = 90;
          break;
        case DEAD_MapObjectDirection::VERTICAL:
          angle = 0;
          break;
        }
      }

      this->renderRect.x =
          (j - this->renderAnchor.x) * this->renderBlockSize + windowWidthMid;

      const SDL_Rect *locationRect;
      bool isAir = false;

      SDL_Rect objectTextureRect = mapObjects[i][j]->getTextureRect();
      if (objectTextureRect.w == 0 && objectTextureRect.h == 0)
        isAir = true;

      if (!isAir) {

        SDL_RenderCopyEx(this->renderer, this->mapObjectTexture,
                         &objectTextureRect, &renderRect, angle, NULL,
                         SDL_RendererFlip::SDL_FLIP_NONE);
      }
    }
  }
}

void DEAD_Renderer::renderPlayer(DEAD_Player *player) {
  this->renderEntity(player, this->playerTexture);
}

void DEAD_Renderer::renderEntity(DEAD_Entity *entity, SDL_Texture *texture) {
  DEAD_Map::MapLocation pos = entity->getPos();
  SDL_Rect rect = entity->getTextureRect();

  int renderRectX = this->getEntityRenderLocation(entity, false).x;
  int renderRectY = this->getEntityRenderLocation(entity, false).y;
  SDL_Rect renderRect = {.x = renderRectX,
                         .y = renderRectY,
                         .w = (int)(entity->getSize() * this->renderBlockSize),
                         .h = (int)(entity->getSize() * this->renderBlockSize)};
  SDL_RenderCopyEx(this->renderer, texture, &rect, &renderRect,
                   entity->getRotation(), NULL, SDL_FLIP_NONE);
}

void DEAD_Renderer::renderZombies(DEAD_ZombieDirector *zombieDirector) {
  std::set<DEAD_Zombie *> knockbackingZombies;
  for (const std::unique_ptr<DEAD_Zombie> &zombie :
       zombieDirector->getZombies()) {
    if (zombie->checkIfInKnockback())
      SDL_SetTextureColorMod(this->zombiesTexture, 100, 100, 100);
    else
      SDL_SetTextureColorMod(this->zombiesTexture, 255, 255, 255);
    renderEntity(zombie.get(), this->zombiesTexture);
  }
}

ScreenLocation DEAD_Renderer::getEntityRenderLocation(DEAD_Entity *entity,
                                                      bool mid) {
  ScreenLocation loc;
  loc.x = (entity->getPos().x - renderAnchor.x) * this->renderBlockSize -
          (entity->getSize() * this->renderBlockSize) / 2.0 +
          this->game->SCREEN_WIDTH / 2.0;
  loc.y = (entity->getPos().y - renderAnchor.y) * this->renderBlockSize -
          (entity->getSize() * this->renderBlockSize) / 2.0 +
          this->game->SCREEN_HEIGHT / 2.0;

  if (mid) {
    loc.x = loc.x + (entity->getSize() * this->renderBlockSize) / 2.0;
    loc.y = loc.y + (entity->getSize() * this->renderBlockSize) / 2.0;
  }
  return loc;
}

void DEAD_Renderer::renderBullets() {
  DEAD_BulletDirector *director = this->game->getBulletDirector();
  std::set<std::unique_ptr<DEAD_Bullet>> &bullets = director->getBullets();

  for (const std::unique_ptr<DEAD_Bullet> &bullet : bullets) {
    SDL_Rect textureRect = bullet->getBulletTextureRect();
    SDL_Rect renderRect = {
        .x = this->getBulletRenderLocation(bullet.get()).x,
        .y = this->getBulletRenderLocation(bullet.get()).y,
        .w = (int)(bullet->getBulletSize() * this->renderBlockSize),
        .h = (int)(bullet->getBulletSize() * this->renderBlockSize)};
    SDL_RenderCopy(this->renderer, this->bulletTexture, &textureRect,
                   &renderRect);
  }
}

ScreenLocation DEAD_Renderer::getBulletRenderLocation(DEAD_Bullet *bullet) {
  ScreenLocation loc;
  loc.x =
      (bullet->getMapLocation().x - renderAnchor.x) * this->renderBlockSize -
      bullet->getBulletSize() * this->renderBlockSize / 2.0 +
      this->game->SCREEN_WIDTH / 2.0;
  loc.y =
      (bullet->getMapLocation().y - renderAnchor.y) * this->renderBlockSize -
      bullet->getBulletSize() * this->renderBlockSize / 2.0 +
      this->game->SCREEN_HEIGHT / 2.0;

  return loc;
}

void DEAD_Renderer::renderItemDropLayer() {
  DEAD_ItemDropLayer *itemDropLayer = this->game->getItemDropLayer();
  const std::set<std::shared_ptr<DEAD_ItemDrop>> &itemDrops =
      itemDropLayer->getItemDrops();

  for (const std::shared_ptr<DEAD_ItemDrop> &itemDrop : itemDrops) {
    SDL_Rect textureRect = itemDrop->getItem()->getItemTextureRect();
    SDL_Rect renderRect = {
        .x = this->getItemDropRenderLocation(itemDrop).x,
        .y = this->getItemDropRenderLocation(itemDrop).y,
        .w = (int)(itemDrop->getSize() * this->renderBlockSize),
        .h = (int)(itemDrop->getSize() * this->renderBlockSize)};
    SDL_RenderCopy(this->renderer, this->itemTexture, &textureRect,
                   &renderRect);
  }
}

ScreenLocation DEAD_Renderer::getItemDropRenderLocation(
    const std::shared_ptr<DEAD_ItemDrop> &itemDrop) {
  ScreenLocation loc;
  loc.x = (itemDrop->getLoc().x - renderAnchor.x) * this->renderBlockSize -
          itemDrop->getSize() * this->renderBlockSize / 2.0 +
          this->game->SCREEN_WIDTH / 2.0;
  loc.y = (itemDrop->getLoc().y - renderAnchor.y) * this->renderBlockSize -
          itemDrop->getSize() * this->renderBlockSize / 2.0 +
          this->game->SCREEN_HEIGHT / 2.0;

  return loc;
}

void DEAD_Renderer::drawZombieMovementMap() {
  DEAD_ZombieDirector *zombieDirector = this->game->getZombieDirector();
  DEAD_Map::MapLocation playerLoc = this->getGame()->getPlayer()->getPos();
  for (int y = 0; y < this->game->getMap()->getMapSize().height; y++) {
    for (int x = 0; x < this->game->getMap()->getMapSize().width; x++) {
      ZombieVector drawingVector =
          zombieDirector->getZombieMovementMaps()->getMovementGradient(
              playerLoc.x, playerLoc.y, x, y);
      ScreenLocation startLoc = this->getPointRenderLocation(x + 0.5, y + 0.5);
      ScreenLocation endLoc = this->getPointRenderLocation(
          x + 0.5 + drawingVector.vectorX, y + 0.5 + drawingVector.vectorY);
      SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
      SDL_RenderDrawLine(this->renderer, startLoc.x, startLoc.y, endLoc.x,
                         endLoc.y);
    }
  }

  for (const std::unique_ptr<DEAD_Zombie> &zombie :
       this->game->getZombieDirector()->getZombies()) {
    ScreenLocation zombieLoc =
        this->getPointRenderLocation(zombie->getPos().x, zombie->getPos().y);
    ZombieVector zombieMoveVec = zombieDirector->getMovementVector(
        zombie->getPos().x, zombie->getPos().y);
    ScreenLocation zombieMoveEndScreen = this->getPointRenderLocation(
        zombieMoveVec.vectorX + zombie->getPos().x,
        zombieMoveVec.vectorY + zombie->getPos().y);
    SDL_RenderDrawLine(this->renderer, zombieLoc.x, zombieLoc.y,
                       zombieMoveEndScreen.x, zombieMoveEndScreen.y);
  }
}

ScreenLocation DEAD_Renderer::getPointRenderLocation(double x, double y) {
  ScreenLocation loc;
  loc.x = (x - renderAnchor.x) * this->renderBlockSize +
          this->game->SCREEN_WIDTH / 2.0;
  loc.y = (y - renderAnchor.y) * this->renderBlockSize +
          this->game->SCREEN_HEIGHT / 2.0;

  return loc;
}

void DEAD_Renderer::moveRenderAnchor(double x, double y) {
  RenderAnchor anchor = {.x = x, .y = y};
  this->renderAnchor = anchor;
}

void DEAD_Renderer::renderYouDied() {

  if (playingYouDied == false)
    return;

  if (this->youDiedAlpha < 200) {
    this->youDiedAlpha = (SDL_GetTicks64() - this->startYouDiedTicks) / 20;
  }
  int rectHeight = this->game->SCREEN_HEIGHT / 3.0;
  SDL_Rect rect = {.x = 0,
                   .y = (this->game->SCREEN_HEIGHT / 2) - rectHeight / 2,
                   .w = this->game->SCREEN_WIDTH,
                   .h = rectHeight};
  std::cout << "Alpha: " << this->youDiedAlpha << std::endl;
  SDL_SetRenderDrawColor(this->renderer, 82, 11, 11, this->youDiedAlpha);
  SDL_RenderFillRect(this->renderer, &rect);
  SDL_SetTextureAlphaMod(this->youDiedFontTexture, this->youDiedAlpha);
  rect.y += rect.y / 4;
  rect.w -= rect.w / 1.7;
  rect.x = this->getGame()->SCREEN_WIDTH / 2 - rect.w / 2;
  rect.h = rect.h / 2;

  std::ifstream quoteFile(DEAD_FilePaths::DEAD_QUOTE_FILE);
  std::string line;

  while (getline(quoteFile, line))
    ;

  std::cout << "The Quote: " << std::endl;
  std::cout << line << std::endl;

  SDL_Texture *infoTexture;
  std::string infoText =
      this->getGame()->getPlayer()->getEntityName() + " survived " +
      std::to_string(this->game->getPassTicks() / 1000) + " second(s)\n";
  this->getTextureFromFont(DEAD_FilePaths::YOU_DIED_FONT, infoTexture, infoText,
                           12, {255, 255, 255, 255});
  SDL_SetTextureAlphaMod(infoTexture, this->youDiedAlpha);
  SDL_Rect infoRenderRect = {.x = this->getGame()->SCREEN_WIDTH / 2,
                             .y = rect.y + rect.h +
                                  this->getGame()->SCREEN_HEIGHT / 20,
                             .w = 0,
                             .h = 0};
  SDL_QueryTexture(infoTexture, NULL, NULL, &infoRenderRect.w,
                   &infoRenderRect.h);
  infoRenderRect.x -= infoRenderRect.w / 2;

  SDL_Texture *quoteTexture;
  std::string quoteText = line;
  this->getTextureFromFont(DEAD_FilePaths::YOU_DIED_FONT, quoteTexture, quoteText,
                           12, {255, 255, 255, 255});
  SDL_SetTextureAlphaMod(quoteTexture, this->youDiedAlpha);
  SDL_Rect quoteRenderRect = {.x = this->getGame()->SCREEN_WIDTH / 2,
                             .y = infoRenderRect.y + infoRenderRect.h,
                             .w = 0,
                             .h = 0};
  SDL_QueryTexture(quoteTexture, NULL, NULL, &quoteRenderRect.w,
                   &quoteRenderRect.h);
  quoteRenderRect.x -= quoteRenderRect.w / 2;

  SDL_RenderCopy(this->renderer, this->youDiedFontTexture, NULL, &rect);
  SDL_RenderCopy(this->renderer, infoTexture, NULL, &infoRenderRect);
  SDL_RenderCopy(this->renderer, quoteTexture, NULL, &quoteRenderRect);

  SDL_DestroyTexture(infoTexture);
  SDL_DestroyTexture(quoteTexture);
}

void DEAD_Renderer::startYouDied() {
  this->startYouDiedTicks = SDL_GetTicks64();
  this->playingYouDied = true;
}

void DEAD_Renderer::closeYouDied() {
  if (!this->playingYouDied)
    return;
  this->youDiedAlpha = 0;
}
