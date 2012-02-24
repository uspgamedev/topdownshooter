#ifndef TOPDOWN_GAME_COMPONENT_PHYSICS_H_
#define TOPDOWN_GAME_COMPONENT_PHYSICS_H_

#include "game.h"

namespace game {
namespace component {

class Physics {
  public:
    Physics();
    ~Physics();

    void Update(double dt, GameObject* owner);
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_PHYSICS_H_