#include <ugdk/base/engine.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/drawable/solidrectangle.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/time/timeaccumulator.h>
#include <ugdk/math/vector2D.h>
#include <pyramidworks/geometry/rect.h>
#include <pyramidworks/collision/collisionlogic.h>

#include "game/builder/objectbuilder.h"

#include "game/gameobject.h"
#include "game/component/graphic.h"
#include "game/component/damageable.h"
#include "game/component/playercontroller.h"
#include "game/component/aicontroller.h"
#include "game/component/idlecontroller.h"

namespace game {
namespace builder {

COLLISION_DIRECT(double, DamageCollision, obj) {
	GameObject *game_obj = (GameObject *) obj;
    if(game_obj->damageable_component())
        game_obj->damageable_component()->Damage(data_);
}

GameObject* ObjectBuilder::BuildHero() {
    GameObject* hero = new GameObject(new component::Graphic, new component::PlayerController, new component::Damageable(10.0));

    ugdk::graphic::SolidRectangle* graphic = new ugdk::graphic::SolidRectangle(ugdk::Vector2D(15.0, 15.0));
    graphic->set_color(ugdk::Color(0.25, 1.00, 0.25));
    graphic->set_hotspot(ugdk::graphic::Drawable::CENTER);
    hero->graphic_component()->node()->set_drawable(graphic);

    hero->collision_object()->InitializeCollisionClass("Hero");
    hero->collision_object()->set_shape(new pyramidworks::geometry::Rect(15.0, 15.0));

    return hero;
}

GameObject* ObjectBuilder::BuildEnemy() {
    GameObject* enemy = new GameObject(new component::Graphic, new component::AiController, new component::Damageable(4.0));

    ugdk::graphic::SolidRectangle* graphic = new ugdk::graphic::SolidRectangle(ugdk::Vector2D(15.0, 15.0));
    graphic->set_color(ugdk::Color(1.00, 0.25, 0.25));
    graphic->set_hotspot(ugdk::graphic::Drawable::CENTER);
    enemy->graphic_component()->node()->set_drawable(graphic);

    enemy->collision_object()->InitializeCollisionClass("Enemy");
    enemy->collision_object()->set_shape(new pyramidworks::geometry::Rect(15.0, 15.0));

    return enemy;
}

GameObject* ObjectBuilder::BuildProjectile(const ugdk::Vector2D& direction, double velocity) {
    GameObject* projectile = new GameObject(new component::Graphic, new component::IdleController);
    projectile->set_velocity(direction * velocity);
    projectile->set_timed_life(new ugdk::time::TimeAccumulator(4000));

    ugdk::graphic::SolidRectangle* graphic = new ugdk::graphic::SolidRectangle(ugdk::Vector2D(5.0, 5.0));
    graphic->set_color(ugdk::Color(0.25, 0.25, 1.00));
    graphic->set_hotspot(ugdk::graphic::Drawable::CENTER);
    projectile->graphic_component()->node()->set_drawable(graphic);

    projectile->collision_object()->InitializeCollisionClass("Projectile");
    projectile->collision_object()->set_shape(new pyramidworks::geometry::Rect(5.0, 5.0));
    projectile->collision_object()->AddCollisionLogic("Enemy", new DamageCollision(5.0));

    return projectile;
}

} // namespace builder
} // namespace game