#ifndef TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_
#define TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_

#include <ugdk/math/vector2D.h>
#include <pyramidworks/collision.h>
#include "game.h"

namespace game {
namespace builder {

class ObjectBuilder {
  public:
    ObjectBuilder(pyramidworks::collision::CollisionManager* manager)
        : manager_(manager) {}
    ~ObjectBuilder() {}

    GameObject* BuildHero();
    GameObject* BuildEnemy();
    GameObject* BuildProjectile(const ugdk::Vector2D& direction, double velocity = 200);

  private:
    pyramidworks::collision::CollisionManager* manager_;
};

} // namespace builder
} // namespace game

#endif // TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_