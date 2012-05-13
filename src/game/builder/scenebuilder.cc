#include <functional>
#include <ugdk/action/generictask.h>
#include <ugdk/base/engine.h>
#include <ugdk/graphic/drawable/solidrectangle.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/modifier.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/time/timeaccumulator.h>
#include <pyramidworks/collision/collisionmanager.h>

#include "game/builder/scenebuilder.h"

#include "game/gameobject.h"
#include "game/builder/objectbuilder.h"


namespace game {
namespace builder {

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

struct PogScene : public Scene {};

Scene* SceneBuilder::BuildRandomScene() {
    ugdk::Vector2D map_size(500.0, 500.0);

    ugdk::Vector2D top_left;
    ugdk::ikdtree::Box<2> box(top_left.val, map_size.val);
    CollisionManager* collision_manager = new CollisionManager(box);
    collision_manager->Generate("Object");
    collision_manager->Generate("Creature", "Object");
    collision_manager->Generate("Hero", "Creature");
    collision_manager->Generate("Enemy", "Creature");
    collision_manager->Generate("Projectile", "Object");

    Scene* controller = new PogScene();

    ugdk::graphic::SolidRectangle* background_rect = new ugdk::graphic::SolidRectangle(map_size);
    controller->content_node()->set_drawable(background_rect);

    ObjectBuilder builder(map_size, collision_manager);
    for(int i = 0; i < 5; ++i) {
        GameObject* enemy = builder.BuildEnemy();
        enemy->set_world_position(ugdk::Vector2D(getRandomNumber(0.0, map_size.x), getRandomNumber(0.0, map_size.y)));
        controller->QueuedAddEntity(enemy);
    }
    GameObject* hero = builder.BuildHero();
    hero->set_world_position(map_size * 0.5);
    controller->QueuedAddEntity(hero);

    controller->AddTask(new TimedLifeTask(controller, 15000));
    controller->AddTask(collision_manager->GenerateHandleCollisionTask());
    controller->AddTask(new GenericTask(bind(UpdateCamera, hero, controller->content_node(), _1)));

    return controller;
}

} // namespace builder
} // namespace game