#include <cstdlib>
#include <functional>
#include <ugdk/action/generictask.h>
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

using namespace std::tr1::placeholders;
using std::tr1::bind;
using ugdk::action::Scene;
using ugdk::action::GenericTask;
using pyramidworks::collision::CollisionInstance;
using pyramidworks::collision::CollisionManager;

static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}

class TimedLifeTask : public ugdk::action::Task {
public:
    TimedLifeTask(Scene* scene, int time)
        :   scene_(scene), 
            time_left_(new ugdk::time::TimeAccumulator(time)) {}

    ~TimedLifeTask() { delete time_left_; }

    void operator()(double dt) {
        if(time_left_->Expired()) {
            finished_ = true;
            scene_->Finish();
        }
    }

private:
    Scene* scene_;
    ugdk::time::TimeAccumulator* time_left_;
};

static bool UpdateCamera(GameObject* reference, ugdk::graphic::Node* node, double dt) {
    if(reference->dead()) return false;
    node->modifier()->set_offset(VIDEO_MANAGER()->video_size() * 0.5 - reference->world_position());
    return true;
}

GameController::GameController() 
    :   map_size_(500.0, 500.0),
        collision_manager_(nullptr)
    {
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
        this->QueuedAddEntity(enemy);
    }
    GameObject* hero = builder.BuildHero();
    hero->set_world_position(map_size_ * 0.5);
    this->QueuedAddEntity(hero);

    this->AddTask(new TimedLifeTask(this, 15000));
    this->AddTask(collision_manager_->GenerateHandleCollisionTask());
    this->AddTask(new GenericTask(bind(UpdateCamera, hero, content_node(), _1)));
}

} // namespace game