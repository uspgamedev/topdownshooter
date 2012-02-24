#ifndef TOPDOWN_GAME_COMPONENT_CONTROLLER_H_
#define TOPDOWN_GAME_COMPONENT_CONTROLLER_H_

#include <ugdk/graphic.h>
#include "game.h"

namespace game {
namespace component {

class Controller {
  //typedef ugdk::Scene super;
  public:
    Controller() {}
    ~Controller() {}

    void Update(double dt, GameObject* owner);

  private:
    static const double VELOCITY;
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_CONTROLLER_H_