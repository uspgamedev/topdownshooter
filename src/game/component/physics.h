#ifndef TOPDOWN_GAME_COMPONENT_PHYSICS_H_
#define TOPDOWN_GAME_COMPONENT_PHYSICS_H_

#include <ugdk/math/vector2D.h>
#include "game.h"

namespace game {
namespace component {

class Physics {
  public:
    Physics(const ugdk::Vector2D& bounds);
    ~Physics();

    void Update(double dt, GameObject* owner);
  private:
    ugdk::Vector2D bounds_;
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_PHYSICS_H_