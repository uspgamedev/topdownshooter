#include <ugdk/time/timeaccumulator.h>
#include <ugdk/graphic/node.h>
#include <pyramidworks/collision/collisionobject.h>

#include "game/gameobject.h"

#include "game/gamecontroller.h"
#include "game/component/graphic.h"
#include "game/component/controller.h"
#include "game/component/damageable.h"
#include "game/component/physics.h"

namespace game {

GameObject::GameObject(pyramidworks::collision::CollisionManager* manager,
    component::Graphic* graphic, component::Controller* controller, 
    component::Physics* physics, component::Damageable* damageable)
  
  : graphic_component_(graphic),
    controller_component_(controller),
    damageable_component_(damageable),
    physics_component_(physics),
    timed_life_(nullptr) {
        
        collision_object_ = new pyramidworks::collision::CollisionObject(manager, this);
}

GameObject::~GameObject() {
    delete graphic_component_;
    delete controller_component_;
    delete physics_component_;
    if(timed_life_) delete timed_life_;
    delete collision_object_;
    if(damageable_component_) delete damageable_component_;
}

void GameObject::Update(double dt) {
    controller_component_->Update(dt, this);
    physics_component_->Update(dt, this);
    graphic_component_->Update(dt, this);
    if(damageable_component_) damageable_component_->Update(dt, this);
    if(timed_life_ && timed_life_->Expired()) Die();
}

void GameObject::set_world_position(const ugdk::Vector2D& position) {
    world_position_ = position;
    collision_object_->MoveTo(position);
}

void GameObject::OnSceneAdd(ugdk::action::Scene* scene) {
    game_controller_ = static_cast<GameController*>(scene);
    collision_object_->StartColliding();
    if(graphic_component_ && graphic_component_->node())
        scene->content_node()->AddChild(graphic_component_->node());
}

} // namespace game