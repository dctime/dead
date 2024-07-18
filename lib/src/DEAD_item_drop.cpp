#include <DEAD_item_drop.h>
#include <SDL2/SDL_log.h>
#include <memory>

DEAD_ItemDrop::DEAD_ItemDrop(std::shared_ptr<DEAD_Item> item)
  : item(item) {
  SDL_Log("Item Drop Created");
}
