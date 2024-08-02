#include "DEAD_filepaths.h"
#include <DEAD_game.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <ui/DEAD_zombie_indicator_ui.h>

DEAD_ZombieIndicatorUI::DEAD_ZombieIndicatorUI(DEAD_Renderer *renderer)
    : DEAD_UI(renderer), loc({.x = 10, .y = 10}),
      font(TTF_OpenFont(DEAD_FilePaths::YOU_DIED_FONT.c_str(), 24)) {
  updateFontTexture();
}

DEAD_ZombieIndicatorUI::~DEAD_ZombieIndicatorUI() { TTF_CloseFont(font); }

void DEAD_ZombieIndicatorUI::updateFontTexture() {
  std::string zombiesLeftText;
  std::string zombieKillcountText;

  zombiesLeftText =
      "Zombies Left: " +
      std::to_string(this->game->getZombieDirector()->getZombies().size());
  zombieKillcountText =
      "Zombies Kill Count: " +
      std::to_string(this->game->getPlayer()->getZombieKillCount());
  SDL_Surface *zombiesLeftSurface = TTF_RenderText_Solid(
      this->font, zombiesLeftText.c_str(), {255, 255, 255, 255});
  this->zombiesLeftFontTexture = SDL_CreateTextureFromSurface(
      this->renderer->getSDLRenderer(), zombiesLeftSurface);
  SDL_FreeSurface(zombiesLeftSurface);

  SDL_Surface *zombiesKillcountSurface = TTF_RenderText_Solid(
      this->font, zombieKillcountText.c_str(), {255, 255, 255, 255});
  this->zombieKillcountFontTexture = SDL_CreateTextureFromSurface(
      this->renderer->getSDLRenderer(), zombiesKillcountSurface);
  SDL_FreeSurface(zombiesKillcountSurface);
}

void DEAD_ZombieIndicatorUI::render() {
  this->updateFontTexture();
  SDL_Rect renderRect = {.x = loc.x, .y = loc.y, .w = 0, .h = 0};
  SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 255, 255, 255, 255);
  SDL_QueryTexture(this->zombiesLeftFontTexture, NULL, NULL, &renderRect.w,
                   &renderRect.h);
  SDL_RenderCopy(this->renderer->getSDLRenderer(), this->zombiesLeftFontTexture,
                 NULL, &renderRect);

  renderRect.y += renderRect.h;
  SDL_QueryTexture(this->zombieKillcountFontTexture, NULL, NULL,
                   &renderRect.w, &renderRect.h);

  SDL_RenderCopy(this->renderer->getSDLRenderer(),
                 this->zombieKillcountFontTexture, NULL, &renderRect);
}
