#pragma once

#include <cstdint>
class DEAD_PlayerMemoriableManager;

class DEAD_IPlayerMemoriableObject {
public:
  virtual DEAD_PlayerMemoriableManager* getMemoryManager() = 0;
};

class DEAD_PlayerMemoriableManager {
public:
  DEAD_PlayerMemoriableManager();
  bool isVisible();
  void setToVisible();
  int getAlpha();
  void gainAlpha(int value);
private:
  bool visible;
  int alpha;
};
