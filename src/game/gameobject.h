#ifndef TOPDOWN_GAME_GAMEOBJECT_H_
#define TOPDOWN_GAME_GAMEOBJECT_H_

#include <ugdk/action/entity.h>
#include <ugdk/math/vector2D.h>
#include <ugdk/time.h>
#include <pyramidworks/collision.h>
#include "game/component.h"
#include "game.h"

namespace game {

class GameObject : public ugdk::action::Entity {
  public:
    GameObject(pyramidworks::collision::CollisionManager*, component::Graphic*, 
        component::Controller*, component::Physics*, component::Damageable* = nullptr);
    ~GameObject();

    void Update(double dt);

    component::Graphic*       graphic_component() { return    graphic_component_; }
    component::Controller* controller_component() { return controller_component_; }
    component::Damageable* damageable_component() { return damageable_component_; }
    component::Physics*       physics_component() { return    physics_component_; }

    void set_world_position(const ugdk::Vector2D& position);
    const ugdk::Vector2D& world_position() const { return world_position_; }

    void set_velocity(const ugdk::Vector2D& velocity) { velocity_ = velocity; }
          ugdk::Vector2D& velocity()       { return velocity_; }
    const ugdk::Vector2D& velocity() const { return velocity_; }

    pyramidworks::collision::CollisionObject* collision_object() { return collision_object_; }

    void Die() { to_be_removed_ = true; }
    bool dead() const { return to_be_removed(); }

    GameController* game_controller() { return game_controller_; }
    void set_game_controller(GameController* game) { game_controller_ = game; }

    void set_timed_life(ugdk::time::TimeAccumulator* timed_life) { timed_life_ = timed_life; }

    void OnSceneAdd(ugdk::action::Scene* scene);

  private:
    component::Graphic*       graphic_component_;
    component::Controller* controller_component_;
    component::Damageable* damageable_component_;
    component::Physics*       physics_component_;
    
    ugdk::time::TimeAccumulator* timed_life_;
    ugdk::Vector2D world_position_;
    ugdk::Vector2D velocity_;
    pyramidworks::collision::CollisionObject* collision_object_;
    GameController* game_controller_;
};

} // namespace game

#endif // TOPDOWN_GAME_GAMEOBJECT_H_