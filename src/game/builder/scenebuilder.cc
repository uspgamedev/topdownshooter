
#include "game/builder/scenebuilder.h"

#include "game/gameobject.h"
#include "game/gamescene.h"
#include "game/builder/objectbuilder.h"

#include <ugdk/action/scene.h>
#include <ugdk/ui/drawable/texturedrectangle.h>
#include <ugdk/ui/node.h>
#include <ugdk/graphic/geometry.h>
#include <ugdk/graphic/module.h>
#include <ugdk/graphic/rendertarget.h>
#include <ugdk/system/compatibility.h>
#include <pyramidworks/collision/collisionmanager.h>

#include <functional>

namespace game {
namespace builder {
namespace SceneBuilder {

using namespace std::placeholders;
using namespace ugdk;
using std::bind;
using ugdk::action::Scene;
using pyramidworks::collision::CollisionInstance;
using pyramidworks::collision::CollisionManager;

static double getRandomNumber(double min, double max) {
    double n = rand();
    return min + (max - min) * (n / RAND_MAX);
}

static bool UpdateCamera(GameObject* reference, ugdk::ui::Node* node, double dt) {
    if(reference->dead()) return false;    
    node->geometry().set_offset(ugdk::graphic::manager()->screen()->size() * 0.5 - reference->world_position());
    return true;
}

std::unique_ptr<ugdk::action::Scene> BuildRandomScene() {
    math::Vector2D map_size(500.0, 500.0);

    math::Vector2D top_left;
    structure::Box<2>::Point p1 = top_left, p2 = map_size;
    structure::Box<2> box(p1, p2);
    

    GameScene* controller = new GameScene(15000, MakeUnique<CollisionManager>(box));
    std::unique_ptr<ugdk::action::Scene> result(controller);
    controller->content_node()->set_drawable(MakeUnique<ui::TexturedRectangle>(graphic::manager()->white_texture(), map_size));

    CollisionManager* collision_manager = controller->collision();
    //collision_manager->ChangeClassParent("Object");
    collision_manager->ChangeClassParent("Creature", "Object");
    collision_manager->ChangeClassParent("Hero", "Creature");
    collision_manager->ChangeClassParent("Enemy", "Creature");
    collision_manager->ChangeClassParent("Projectile", "Object");

    ObjectBuilder builder(map_size);
    for(int i = 0; i < 5; ++i) {
        auto enemy = builder.BuildEnemy();
        enemy->set_world_position(ugdk::math::Vector2D(getRandomNumber(0.0, map_size.x), getRandomNumber(0.0, map_size.y)));
        controller->QueuedAddEntity(enemy);
    }
    auto hero = builder.BuildHero();
    hero->set_world_position(map_size * 0.5);
    controller->QueuedAddEntity(hero);

    controller->AddTask(collision_manager->GenerateHandleCollisionTask(0.5));
    controller->AddTask(bind(UpdateCamera, hero.get(), controller->content_node().get(), _1));

    return result;
}

} // namespace SceneBuilder
} // namespace builder
} // namespace game