#ifndef TOPDOWN_GAME_COMPONENT_GRAPHIC_H_
#define TOPDOWN_GAME_COMPONENT_GRAPHIC_H_

#include <ugdk/ui.h>
#include "game.h"

namespace game {
namespace component {

class Graphic {
  //typedef ugdk::Scene super;
  public:
    Graphic();
    ~Graphic();

    void Update(double dt, GameObject* owner);

    std::shared_ptr<ugdk::ui::Node> node() { return node_; }
    std::shared_ptr<const ugdk::ui::Node> node() const { return node_; }

  private:
    std::shared_ptr<ugdk::ui::Node> node_;
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_GRAPHIC_H_