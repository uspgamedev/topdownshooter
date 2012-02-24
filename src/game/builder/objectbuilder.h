#ifndef TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_
#define TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_

#include <ugdk/math/vector2D.h>
#include "game.h"

namespace game {
namespace builder {

class ObjectBuilder {
  public:
    ObjectBuilder() {}
    ~ObjectBuilder() {}

    GameObject* BuildHero();
    GameObject* BuildEnemy();
    GameObject* BuildProjectile(const ugdk::Vector2D& direction, double velocity = 200);
};

} // namespace builder
} // namespace game

#endif // TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_