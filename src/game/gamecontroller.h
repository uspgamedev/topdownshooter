#ifndef TOPDOWN_GAME_GAMECONTROLLER_H_
#define TOPDOWN_GAME_GAMECONTROLLER_H_

#include <list>
#include <ugdk/action/scene.h>
#include <ugdk/time.h>
#include <pyramidworks/collision.h>
#include "game.h"

namespace game {

class GameController : public ugdk::action::Scene {
  typedef ugdk::action::Scene super;
  public:
    GameController();
    ~GameController();

    void Update(double dt);

    void AddGameObject(GameObject* game_object);

    const ugdk::Vector2D& map_size() const { return map_size_; }

    pyramidworks::collision::CollisionManager* collision_manager() { return collision_manager_; }

  private:
    typedef std::list<GameObject*> GameObjectList;
    void ClearDeadGameObjects();
    void AddPendingGameObjects();

    ugdk::Vector2D map_size_;
    ugdk::time::TimeAccumulator* time_left_;
    GameObject* hero_;

    GameObjectList game_objects_;
    GameObjectList pending_game_objects_;

    pyramidworks::collision::CollisionManager* collision_manager_;
};

} // namespace game

#endif // TOPDOWN_GAME_GAMECONTROLLER_H_