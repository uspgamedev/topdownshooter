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
    virtual ~Controller() {}

    virtual void Update(double dt, GameObject* owner) = 0;
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_CONTROLLER_H_