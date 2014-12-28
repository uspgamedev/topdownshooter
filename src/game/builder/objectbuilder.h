#ifndef TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_
#define TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_

#include <ugdk/math/vector2D.h>
#include <pyramidworks/collision.h>
#include "game.h"

#include <memory>

namespace game {
namespace builder {

class ObjectBuilder {
  public:
      ObjectBuilder(const ugdk::math::Vector2D& map_size)
        : map_size_(map_size) {}
    ~ObjectBuilder() {}

    std::shared_ptr<GameObject> BuildHero();
    std::shared_ptr<GameObject> BuildEnemy();
    std::shared_ptr<GameObject> BuildProjectile(const ugdk::math::Vector2D& direction, double velocity = 200);

  private:
    ugdk::math::Vector2D map_size_;
};

} // namespace builder
} // namespace game

#endif // TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_