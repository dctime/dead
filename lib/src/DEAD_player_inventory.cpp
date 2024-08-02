#include "DEAD_player.h"
#include <DEAD_player_inventory.h>
#include <DEAD_game.h>
#include <cstdint>
#include <iostream>
#include <memory>

// use replaceholditem to change hotbar current holding item

DEAD_PlayerInventory::DEAD_PlayerInventory(DEAD_Player* player)
  : hotbarIndex(0), player(player), INVENTORY_SIZE(3) {
  this->hotbar.resize(INVENTORY_SIZE);
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

uint8_t DEAD_PlayerInventory::getHotbarIndex() {
  return this->hotbarIndex;
}

void DEAD_PlayerInventory::nextItemHotbar() {
  this->hotbarIndex += 1;
  if (this->hotbarIndex >= this->hotbar.size()) {
    this->hotbarIndex = 0;
  }
  this->player->setHoldItem(this->hotbar.at(this->hotbarIndex));
}

void DEAD_PlayerInventory::previousItemHotbar() {
  if (this->hotbarIndex == 0) {
    this->hotbarIndex = this->hotbar.size()-1;
  } else {
    this->hotbarIndex -= 1;
  }

  std::cout << "Now Index: " << this->hotbarIndex << std::endl;
  this->player->setHoldItem(this->hotbar.at(this->hotbarIndex));
}

void DEAD_PlayerInventory::switchItemHotbar(uint8_t index) {
  if (index < 0 || index >= this->hotbar.size()-1) return;
  this->hotbarIndex = index;
  this->player->setHoldItem(this->hotbar.at(this->hotbarIndex));
}
