
#include <ugdk/ui/node.h>
#include <ugdk/ui/drawable/texturedrectangle.h>
#include <ugdk/graphic/module.h>
#include <ugdk/time/timeaccumulator.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/system/compatibility.h>
#include <pyramidworks/geometry/rect.h>
#include <pyramidworks/collision/collisionobject.h>

#include "game/builder/objectbuilder.h"

#include "game/gameobject.h"
#include "game/component/graphic.h"
#include "game/component/damageable.h"
#include "game/component/physics.h"
#include "game/component/playercontroller.h"
#include "game/component/aicontroller.h"
#include "game/component/idlecontroller.h"

namespace game {
namespace builder {

using namespace ugdk;

pyramidworks::collision::CollisionLogic DamageCollision(int damage) {
    return [damage](const pyramidworks::collision::CollisionObject* obj) {
        if (GameObject *game_obj = dynamic_cast<GameObject*>(obj->data()))
            if (game_obj->damageable_component())
                game_obj->damageable_component()->Damage(damage);
    };
}

std::shared_ptr<GameObject> ObjectBuilder::BuildHero() {
    std::shared_ptr<GameObject> hero(new GameObject(new component::Graphic,
        new component::PlayerController(*this), new component::Physics(map_size_), new component::Damageable(10.0)));

    auto node = hero->graphic_component()->node();
    node->set_drawable(MakeUnique<ugdk::ui::TexturedRectangle>(graphic::manager()->white_texture(), math::Vector2D(15.0, 15.0)));
    node->drawable()->set_hotspot(ui::HookPoint::CENTER);
    node->effect().set_color(Color(0.25, 1.00, 0.25));

    hero->collision_object()->ChangeCollisionClass("Hero");
    hero->collision_object()->ChangeShape(MakeUnique<pyramidworks::geometry::Rect>(15.0, 15.0));

    return hero;
}

std::shared_ptr<GameObject> ObjectBuilder::BuildEnemy() {
    std::shared_ptr<GameObject> enemy(new GameObject(new component::Graphic,
        new component::AiController, new component::Physics(map_size_), new component::Damageable(4.0)));

    auto node = enemy->graphic_component()->node();
    node->set_drawable(MakeUnique<ugdk::ui::TexturedRectangle>(graphic::manager()->white_texture(), math::Vector2D(15.0, 15.0)));
    node->drawable()->set_hotspot(ui::HookPoint::CENTER);
    node->effect().set_color(Color(1.00, 0.25, 0.25));

    enemy->collision_object()->ChangeCollisionClass("Enemy");
    enemy->collision_object()->ChangeShape(MakeUnique<pyramidworks::geometry::Rect>(15.0, 15.0));

    return enemy;
}

std::shared_ptr<GameObject> ObjectBuilder::BuildProjectile(const ugdk::math::Vector2D& direction, double velocity) {
    std::shared_ptr<GameObject> projectile(new GameObject(new component::Graphic,
        new component::IdleController, new component::Physics(map_size_)));
    projectile->set_velocity(direction * velocity);
    projectile->set_timed_life(new ugdk::time::TimeAccumulator(4000));

    auto node = projectile->graphic_component()->node();
    node->set_drawable(MakeUnique<ugdk::ui::TexturedRectangle>(graphic::manager()->white_texture(), math::Vector2D(5.0, 5.0)));
    node->drawable()->set_hotspot(ui::HookPoint::CENTER);
    node->effect().set_color(Color(0.25, 0.25, 1.00));

    projectile->collision_object()->ChangeCollisionClass("Projectile");
    projectile->collision_object()->ChangeShape(MakeUnique<pyramidworks::geometry::Rect>(5.0, 5.0));
    projectile->collision_object()->AddCollisionLogic("Enemy", DamageCollision(5.0));

    return projectile;
}

} // namespace builder
} // namespace game