#include <ugdk/graphic/node.h>
#include <ugdk/time/timeaccumulator.h>

#include "game/gamecontroller.h"

#include "game/gameobject.h"
#include "game/component/graphic.h"
#include "game/component/controller.h"

namespace game {

GameController::GameController() : time_left_(new ugdk::time::TimeAccumulator(5000)) {
    time_left_->Restart();
    this->AddGameObject(new GameObject(new component::Graphic, new component::Controller));
}

GameController::~GameController() {
    delete time_left_;
}

void GameController::Update(double dt) {
    super::Update(dt);
    if(time_left_->Expired()) Finish();

    AddPendingGameObjects();
}

void GameController::AddGameObject(GameObject* game_object) {
    pending_game_objects_.push_back(game_object);
}

void GameController::AddPendingGameObjects() {
    for(GameObjectList::iterator it = pending_game_objects_.begin(); it != pending_game_objects_.end(); ++it) {
        GameObject* new_obj = *it;
        if(new_obj->graphic_component()->node() != nullptr)
            this->content_node()->AddChild(new_obj->graphic_component()->node());
        game_objects_.push_back(new_obj);
    }
    pending_game_objects_.clear();
}

} // namespace game