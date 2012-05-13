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
using pyramidworks::collision::CollisionManager;

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

GameController::GameController() 
    :   map_size_(500.0, 500.0), 
        time_left_(new ugdk::time::TimeAccumulator(15000)), 
        hero_(nullptr),
        collision_manager_(nullptr)
    {
    time_left_->Restart();

    ugdk::Vector2D top_left;
    ugdk::ikdtree::Box<2> box(top_left.val, map_size_.val);
    collision_manager_ = new CollisionManager(box);
    collision_manager_->Generate("Object");
    collision_manager_->Generate("Creature", "Object");
    collision_manager_->Generate("Hero", "Creature");
    collision_manager_->Generate("Enemy", "Creature");
    collision_manager_->Generate("Projectile", "Object");

    ugdk::graphic::SolidRectangle* background_rect = new ugdk::graphic::SolidRectangle(map_size_);
    content_node()->set_drawable(background_rect);

    builder::ObjectBuilder builder(collision_manager_);
    for(int i = 0; i < 5; ++i) {
        GameObject* enemy = builder.BuildEnemy();
        enemy->set_world_position(ugdk::Vector2D(getRandomNumber(0.0, map_size_.x), getRandomNumber(0.0, map_size_.y)));
        this->AddGameObject(enemy);
    }
    this->AddGameObject(hero_ = builder.BuildHero());
    hero_->set_world_position(map_size_ * 0.5);

    this->AddTask(collision_manager_->GenerateHandleCollisionTask());
}

GameController::~GameController() {
    delete time_left_;
    if(hero_ != nullptr) delete hero_;
}

void GameController::Update(double dt) {
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
        game_objects_.push_back(new_obj);
        this->AddEntity(new_obj);
    }
    pending_game_objects_.clear();
}

} // namespace game