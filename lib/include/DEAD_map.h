#include <vector>

class Map {
public:
  Map();
  ~Map();
  void renderMap();
private:
  std::vector<std::vector<int>> mapObjects;
};
