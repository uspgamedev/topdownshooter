#include <ugdk/action/scene.h>
#include <ugdk/time/timeaccumulator.h>
#include <ugdk/ui/node.h>
#include <pyramidworks/collision/collisionobject.h>
#include <pyramidworks/geometry/geometricshape.h>

#include "game/gameobject.h"
#include "game/gamescene.h"

#include "game/component/graphic.h"
#include "game/component/controller.h"
#include "game/component/damageable.h"
#include "game/component/physics.h"

namespace game {

GameObject::GameObject(
    component::Graphic* graphic, component::Controller* controller, 
    component::Physics* physics, component::Damageable* damageable)
  
    :   graphic_component_(graphic)
    ,   controller_component_(controller)
    ,   damageable_component_(damageable)
    ,   physics_component_(physics)
    ,   timed_life_(nullptr)
    ,   to_be_removed_(false)
{        
    collision_object_ = new pyramidworks::collision::CollisionObject(this, "", nullptr);
}

GameObject::~GameObject() {
    delete graphic_component_;
    delete controller_component_;
    delete physics_component_;
    delete timed_life_;
    delete collision_object_;
    delete damageable_component_;
}

void GameObject::Update(double dt) {
    controller_component_->Update(dt, this);
    physics_component_->Update(dt, this);
    graphic_component_->Update(dt, this);
    if(damageable_component_) damageable_component_->Update(dt, this);
    if(timed_life_ && timed_life_->Expired()) Die();
}

void GameObject::set_world_position(const ugdk::math::Vector2D& position) {
    world_position_ = position;
    collision_object_->MoveTo(position);
}

void GameObject::OnSceneAdd(GameScene* scene) {
    game_controller_ = scene;
    collision_object_->StartColliding(scene->collision());
    if(graphic_component_ && graphic_component_->node())
        scene->content_node()->AddChild(graphic_component_->node());
}

} // namespace game