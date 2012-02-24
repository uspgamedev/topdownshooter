#include <ugdk/time/timeaccumulator.h>
#include <pyramidworks/collision/collisionobject.h>

#include "game/gameobject.h"

#include "game/component/graphic.h"
#include "game/component/controller.h"
#include "game/component/damageable.h"

namespace game {

GameObject::GameObject(component::Graphic* graphic, component::Controller* controller, component::Damageable* damageable)
  : graphic_component_(graphic),
    controller_component_(controller),
    damageable_component_(damageable),
    timed_life_(nullptr),
    dead_(false) {
        
        collision_object_ = new pyramidworks::collision::CollisionObject(this);
}

GameObject::~GameObject() {
    delete graphic_component_;
    delete controller_component_;
    if(timed_life_) delete timed_life_;
    delete collision_object_;
    if(damageable_component_) delete damageable_component_;
}

void GameObject::Update(double dt) {
    controller_component_->Update(dt, this);

    set_world_position(world_position_ + velocity_ * dt);

    graphic_component_->Update(dt, this);
    if(damageable_component_) damageable_component_->Update(dt, this);
    if(timed_life_ && timed_life_->Expired()) Die();
}

void GameObject::set_world_position(const ugdk::Vector2D& position) {
    world_position_ = position;
    collision_object_->MoveTo(position);
}

} // namespace game