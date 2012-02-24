#ifndef TOPDOWN_GAME_COMPONENT_PLAYERCONTROLLER_H_
#define TOPDOWN_GAME_COMPONENT_PLAYERCONTROLLER_H_

#include <ugdk/time.h>
#include "game/component/controller.h"
#include "game.h"

namespace game {
namespace component {

class PlayerController : public Controller {
  typedef Controller super;
  public:
    PlayerController();
    ~PlayerController();

    void Update(double dt, GameObject* owner);

  private:
    static const double VELOCITY;
    ugdk::time::TimeAccumulator* fire_cooldown_;
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_PLAYERCONTROLLER_H_