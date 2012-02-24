#include <cstdlib>
#include <ugdk/base/engine.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/drawable/solidrectangle.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/time/timeaccumulator.h>
#include <pyramidworks/collision/collisionmanager.h>
#include <pyramidworks/collision/collisionlogic.h>

#include "game/gamecontroller.h"

#include "game/gameobject.h"
#include "game/component/graphic.h"
#include "game/builder/objectbuilder.h"

namespace game {

using pyramidworks::collision::CollisionInstance;

static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}

static bool objectIsDead (const GameObject* value) {
    bool is_dead = value->dead();
    if (is_dead) {
        delete value;
    }
    return is_dead;
}

GameController::GameController() : time_left_(new ugdk::time::TimeAccumulator(15000)), hero_(nullptr) {
    time_left_->Restart();

    builder::ObjectBuilder builder;
    this->AddGameObject(hero_ = builder.BuildHero());

    ugdk::Vector2D map_size(100, 100);

    for(int i = 0; i < 5; ++i) {
        GameObject* enemy = builder.BuildEnemy();
        enemy->set_world_position(ugdk::Vector2D(getRandomNumber(0.0, map_size.x), getRandomNumber(0.0, map_size.y)));
        this->AddGameObject(enemy);
    }
    ugdk::graphic::SolidRectangle* background_rect = new ugdk::graphic::SolidRectangle(map_size);
    content_node()->set_drawable(background_rect);
}

GameController::~GameController() {
    delete time_left_;
    if(hero_ != nullptr) delete hero_;
}

void GameController::HandleCollisions() {
    std::list<CollisionInstance> collision_list;
    
    // Update objects positions in CollisionManager
    pyramidworks::collision::CollisionManager::reference()->Update();

    GameObjectList::iterator i;
    for (i = game_objects_.begin(); i != game_objects_.end(); ++i)
        (*i)->collision_object()->SearchCollisions(collision_list);

    std::list<CollisionInstance>::iterator it;
    for(it = collision_list.begin(); it != collision_list.end(); ++it) {
        it->first->Handle(it->second);
    }
}

void GameController::Update(double dt) {
    HandleCollisions();
    super::Update(dt);
    if(time_left_->Expired() || hero_->dead()) {
        Finish();
        return;
    }

    content_node()->modifier()->set_offset(VIDEO_MANAGER()->video_size() * 0.5 - hero_->world_position());

    ClearDeadGameObjects();
    AddPendingGameObjects();
}

void GameController::AddGameObject(GameObject* game_object) {
    pending_game_objects_.push_back(game_object);
}

void GameController::ClearDeadGameObjects() {
    for(GameObjectList::iterator it = game_objects_.begin(); it != game_objects_.end(); ++it) {
        if((*it)->dead())
            RemoveEntity(*it);
    }
    game_objects_.remove_if(objectIsDead);
}

void GameController::AddPendingGameObjects() {
    for(GameObjectList::iterator it = pending_game_objects_.begin(); it != pending_game_objects_.end(); ++it) {
        GameObject* new_obj = *it;
        if(new_obj->graphic_component()->node() != nullptr)
            this->content_node()->AddChild(new_obj->graphic_component()->node());
        game_objects_.push_back(new_obj);
        this->AddEntity(new_obj);

        new_obj->set_game_controller(this);
        new_obj->collision_object()->StartColliding();
    }
    pending_game_objects_.clear();
}

} // namespace game