#include "DEAD_renderer.h"
#include "guns/DEAD_gun.h"
#include "ui/DEAD_ui.h"
#include <DEAD_game.h>
#include <SDL2/SDL_pixels.h>
#include <memory>
#include <ui/DEAD_magazine_ui.h>
#include <DEAD_player.h>

DEAD_MagazineUI::DEAD_MagazineUI(std::shared_ptr<DEAD_Renderer> renderer,
                                 std::shared_ptr<DEAD_Player> player)
    : DEAD_UI(renderer), magazineUIWidth(this->game->SCREEN_WIDTH / 3),
      magazineUIHeight(this->game->SCREEN_HEIGHT / 50),
      distanceBetweenScreenBoarder(10), boarderWidth(magazineUIHeight / 4),
      barElement(std::make_shared<DEAD_ValueBarUIElement>(
          renderer, this->game->SCREEN_WIDTH / 2 - this->magazineUIWidth / 2,
          this->game->SCREEN_HEIGHT - this->magazineUIHeight * 2 -
              this->distanceBetweenScreenBoarder - 10,
          this->magazineUIWidth, this->magazineUIHeight,
          this->distanceBetweenScreenBoarder, this->boarderWidth)) {
  this->renderer = renderer;
  this->player = player; 
}

void DEAD_MagazineUI::render() {
  std::shared_ptr<DEAD_Gun> holdGun = std::dynamic_pointer_cast<DEAD_Gun>(this->player->getHoldItem());
  if (holdGun == nullptr) return;

  int magazineSize = holdGun->getMagazineSize();
  int ammoLeftInMagazine = holdGun->getAmmoLeftInMagazine();
  
  double leftPercent = 0;
  double subPercent = 0;
  if (holdGun->checkStillReloading() == 1.0) {
    leftPercent = static_cast<double>(ammoLeftInMagazine) / magazineSize;
    subPercent = holdGun->checkStillCooling();
  } else {
    leftPercent = 0;
    subPercent = holdGun->checkStillReloading();
  }

  SDL_Color baseColor = {.r = 50, .g = 50, .b = 50, .a = 255};
  SDL_Color juiceColor = {.r = 0, .g = 0, .b = 200, .a = 255};
  SDL_Color subColor = {.r=255, .g=255, .b=255, .a=255};
  this->barElement->render(baseColor, juiceColor, subColor, leftPercent, subPercent);
}
