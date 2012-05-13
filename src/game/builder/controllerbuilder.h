#ifndef TOPDOWN_GAME_BUILDER_CONTROLLERBUILDER_H_
#define TOPDOWN_GAME_BUILDER_CONTROLLERBUILDER_H_

#include <ugdk/math/vector2D.h>
#include <pyramidworks/collision.h>
#include "game.h"

namespace game {
namespace builder {

class ControllerBuilder {
  public:
    ControllerBuilder() {}
    ~ControllerBuilder() {}

    GameController* BuildRandomController();
};

} // namespace builder
} // namespace game

#endif // TOPDOWN_GAME_BUILDER_CONTROLLERBUILDER_H_