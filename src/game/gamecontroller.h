#ifndef TOPDOWN_GAME_GAMECONTROLLER_H_
#define TOPDOWN_GAME_GAMECONTROLLER_H_

#include <list>
#include <ugdk/action/scene.h>
#include <ugdk/time.h>
#include "game.h"

namespace game {

class GameController : public ugdk::Scene {
  typedef ugdk::Scene super;
  public:
    GameController();
    ~GameController();

    void Update(double dt);

    void AddGameObject(GameObject* game_object);

  private:
    typedef std::list<GameObject*> GameObjectList;
    void AddPendingGameObjects();

    ugdk::time::TimeAccumulator* time_left_;
    GameObjectList game_objects_;
    GameObjectList pending_game_objects_;
};

} // namespace game

#endif // TOPDOWN_GAME_GAMECONTROLLER_H_