#include "DEAD_player.h"
#include <DEAD_player_inventory.h>
#include <DEAD_game.h>
#include <memory>

// use replaceholditem to change hotbar current holding item

DEAD_PlayerInventory::DEAD_PlayerInventory(DEAD_Player* player)
  : hotbarIndex(0), player(player), inventorySize(3) {
  this->hotbar.resize(inventorySize);
}

const std::vector<std::shared_ptr<DEAD_Item>>& DEAD_PlayerInventory::getHotbar() {
  return this->hotbar;
}

DEAD_Item* DEAD_PlayerInventory::getHoldItem() {
  return this->hotbar.at(this->hotbarIndex).get();
}

void DEAD_PlayerInventory::dropHoldItem() {
  this->player->getGame()->getItemDropLayer()->drop(this->hotbar.at(hotbarIndex)->getItemDrop());
  this->hotbar.at(hotbarIndex)->setPlayer(nullptr);
  this->replaceHoldItem(nullptr);
  SDL_Log("Dropped Weapons Count: %d", this->player->getGame()->getItemDropLayer()->getDropsCount());
}

void DEAD_PlayerInventory::replaceHoldItem(std::shared_ptr<DEAD_Item> item) {
  this->hotbar.at(this->hotbarIndex) = item;
  this->player->setHoldItem(item);
}
