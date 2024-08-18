#pragma once
#include "../DEAD_map.h"
#include "DEAD_label_renderer.h"
#include "DEAD_subrenderer_base.h"
#include <memory>

class DEAD_ShadowCaster : public DEAD_SubRendererBase {
public:
  struct LineStatus {
    int leftLineIndex = -1;
    int rightLineIndex = -1;
    int upLineIndex = -1;
    int downLineIndex = -1;
  };

  class LocLineStatus {
  public:
    LocLineStatus(DEAD_Map *map) {
      for (int y = 0; y < map->getMapSize().height; y++) {
        std::vector<LineStatus> temp;
        for (int x = 0; x < map->getMapSize().width; x++) {
          LineStatus status;
          temp.push_back(status);
        }
        lineStatus.push_back(temp);
      }
    }

    LineStatus getLineStatus(int x, int y, DEAD_Map *map) {
      if ((x < 0 || x >= map->getMapSize().width) || y < 0 ||
          y >= map->getMapSize().height) {
        LineStatus status;
        return status;
      }

      return lineStatus.at(y).at(x);
    }

    LineStatus &setLineStatus(int x, int y) { return lineStatus.at(y).at(x); }

  private:
    std::vector<std::vector<LineStatus>> lineStatus;
  };
  DEAD_ShadowCaster(DEAD_Renderer *renderer);

  void updateShadowCaster();
  void render() override;

private:
  DEAD_Map *map;
  std::unique_ptr<DEAD_LabelRenderer> labelRenderer;
  std::vector<DEAD_Map::MapLine> lines;
  std::set<DEAD_Map::MapLocation> points;
  
};
