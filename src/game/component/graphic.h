#ifndef TOPDOWN_GAME_COMPONENT_GRAPHIC_H_
#define TOPDOWN_GAME_COMPONENT_GRAPHIC_H_

#include <ugdk/graphic.h>
#include "game.h"

namespace game {
namespace component {

class Graphic {
  //typedef ugdk::Scene super;
  public:
    Graphic();
    ~Graphic();

    void Update(double dt, GameObject* owner);

          ugdk::graphic::Node* node()       { return node_; }
    const ugdk::graphic::Node* node() const { return node_; }

  private:
    ugdk::graphic::Node* node_;
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_GRAPHIC_H_