#ifndef TOPDOWN_GAME_COMPONENT_IDLECONTROLLER_H_
#define TOPDOWN_GAME_COMPONENT_IDLECONTROLLER_H_

#include <ugdk/graphic.h>
#include "game/component/controller.h"
#include "game.h"

namespace game {
namespace component {

class IdleController : public Controller {
  typedef Controller super;
  public:
    IdleController() {}
    ~IdleController() {}

    void Update(double dt, GameObject* owner) {}
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_IDLECONTROLLER_H_