#ifndef TOPDOWN_GAME_COMPONENT_PLAYERCONTROLLER_H_
#define TOPDOWN_GAME_COMPONENT_PLAYERCONTROLLER_H_

#include <ugdk/time.h>
#include "game/component/controller.h"
#include "game.h"
#include "game/builder/objectbuilder.h"

#include <memory>

namespace game {
namespace component {

class PlayerController : public Controller {
  typedef Controller super;
  public:
    PlayerController(const builder::ObjectBuilder& builder);
    ~PlayerController();

    void Update(double dt, GameObject* owner);

  private:
    static const double VELOCITY;
    std::unique_ptr<ugdk::time::TimeAccumulator> fire_cooldown_;
    builder::ObjectBuilder builder_;
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_PLAYERCONTROLLER_H_