#include "DEAD_player_inventory.h"
#include "DEAD_renderer.h"
#include <DEAD_game.h>
#include <DEAD_player_inventory_renderer.h>
#include <SDL2/SDL_render.h>

DEAD_PlayerInventoryRenderer::DEAD_PlayerInventoryRenderer(
    DEAD_Renderer *renderer, SDL_Texture *itemTexture)
    : frameWidth(renderer->getGame()->SCREEN_WIDTH / 20),
      itemTexture(itemTexture) {
  this->frameLeftDownLoc = {.x = 20, .y = 20};
  this->renderer = renderer;
  this->frameBoarderWidth = this->frameWidth / 10;
}

void DEAD_PlayerInventoryRenderer::render() { this->renderFrame(); }

void DEAD_PlayerInventoryRenderer::renderFrame() {
  DEAD_PlayerInventory *inventory =
      this->renderer->getGame()->getPlayer()->getInventory();
  int hotbarSize = inventory->getHotbar().size();
  ScreenLocation renderLoc;
  renderLoc.x = frameLeftDownLoc.x;
  renderLoc.y = this->renderer->getGame()->SCREEN_HEIGHT - frameLeftDownLoc.y -
                frameWidth;
  for (int i = 0; i < inventory->getHotbar().size(); i++) {
    SDL_Rect renderScreenRect = {.x = renderLoc.x,
                                 .y = renderLoc.y - i * this->frameWidth,
                                 .w = frameWidth,
                                 .h = frameWidth};
    SDL_Rect renderScreenInnerRect = {
        .x = renderScreenRect.x + this->frameBoarderWidth,
        .y = renderScreenRect.y + this->frameBoarderWidth,
        .w = renderScreenRect.w - this->frameBoarderWidth * 2,
        .h = renderScreenRect.h - this->frameBoarderWidth * 2};
    if (hotbarSize - i - 1 == inventory->getHotbarIndex())
      SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 255, 255, 255,
                             255);
    else
      SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 150, 150, 150,
                             255);
    SDL_RenderFillRect(this->renderer->getSDLRenderer(), &renderScreenRect);
    SDL_SetRenderDrawColor(this->renderer->getSDLRenderer(), 30, 30, 30, 255);
    SDL_RenderFillRect(this->renderer->getSDLRenderer(),
                       &renderScreenInnerRect);
    DEAD_Item *renderingItem =
        inventory->getHotbar().at(hotbarSize - i - 1).get();
    if (renderingItem == nullptr)
      continue;
    SDL_Rect itemTextureRect = (renderingItem->getItemTextureRect());
    SDL_RenderCopy(this->renderer->getSDLRenderer(), this->itemTexture,
                   &itemTextureRect, &renderScreenInnerRect);
  }
}
