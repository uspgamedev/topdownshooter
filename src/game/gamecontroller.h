#ifndef TOPDOWN_GAME_GAMECONTROLLER_H_
#define TOPDOWN_GAME_GAMECONTROLLER_H_

#include <ugdk/action/scene.h>
#include <pyramidworks/collision.h>

namespace game {

class GameController : public ugdk::action::Scene {
  typedef ugdk::action::Scene super;
  public:
    GameController(const ugdk::Vector2D& map_size, pyramidworks::collision::CollisionManager* manager)
        :   map_size_(map_size), collision_manager_(manager) {}

    const ugdk::Vector2D& map_size() const { return map_size_; }
    pyramidworks::collision::CollisionManager* collision_manager() { return collision_manager_; }

  private:
    ugdk::Vector2D map_size_;
    pyramidworks::collision::CollisionManager* collision_manager_;
};

} // namespace game

#endif // TOPDOWN_GAME_GAMECONTROLLER_H_