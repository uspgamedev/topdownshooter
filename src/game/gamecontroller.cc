#include <ugdk/base/engine.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/drawable/solidrectangle.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/time/timeaccumulator.h>

#include "game/gamecontroller.h"

#include "game/gameobject.h"
#include "game/component/graphic.h"
#include "game/builder/objectbuilder.h"

namespace game {

GameController::GameController() : time_left_(new ugdk::time::TimeAccumulator(10000)), hero_(nullptr) {
    time_left_->Restart();

    builder::ObjectBuilder builder;
    this->AddGameObject(hero_ = builder.BuildHero());

    ugdk::Vector2D map_size(100, 100);
    ugdk::graphic::SolidRectangle* background_rect = new ugdk::graphic::SolidRectangle(map_size);
    content_node()->set_drawable(background_rect);
}

GameController::~GameController() {
    delete time_left_;
    if(hero_ != nullptr) delete hero_;
}

void GameController::Update(double dt) {
    super::Update(dt);
    if(time_left_->Expired()) Finish();

    content_node()->modifier()->set_offset(VIDEO_MANAGER()->video_size() * 0.5 - hero_->world_position());

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
        this->AddEntity(new_obj);
    }
    pending_game_objects_.clear();
}

} // namespace game