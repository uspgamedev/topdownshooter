#ifndef TOPDOWN_GAME_COMPONENT_AICONTROLLER_H_
#define TOPDOWN_GAME_COMPONENT_AICONTROLLER_H_

#include <ugdk/graphic.h>
#include <ugdk/time.h>
#include "game/component/controller.h"
#include "game.h"

namespace game {
namespace component {

class AiController : public Controller {
  typedef Controller super;
  public:
    AiController();
    ~AiController();

    void Update(double dt, GameObject* owner);

  private:
    static const double VELOCITY, MIN_WAIT, MAX_WAIT;
    ugdk::time::TimeAccumulator* timer_;
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_AICONTROLLER_H_