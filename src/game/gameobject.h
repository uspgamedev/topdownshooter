#ifndef TOPDOWN_GAME_GAMEOBJECT_H_
#define TOPDOWN_GAME_GAMEOBJECT_H_

#include <ugdk/math/vector2D.h>
#include <ugdk/time.h>
#include <pyramidworks/collision.h>
#include <pyramidworks/collision/collisiondata.h>
#include "game/component.h"
#include "game.h"

namespace game {

class GameObject : public pyramidworks::collision::CollisionData {
  public:
    GameObject(component::Graphic*, component::Controller*, component::Physics*, component::Damageable* = nullptr);
    ~GameObject();

    void Update(double dt);

    component::Graphic*       graphic_component() { return    graphic_component_; }
    component::Controller* controller_component() { return controller_component_; }
    component::Damageable* damageable_component() { return damageable_component_; }
    component::Physics*       physics_component() { return    physics_component_; }

    void set_world_position(const ugdk::math::Vector2D& position);
    const ugdk::math::Vector2D& world_position() const { return world_position_; }

    void set_velocity(const ugdk::math::Vector2D& velocity) { velocity_ = velocity; }
          ugdk::math::Vector2D& velocity()       { return velocity_; }
    const ugdk::math::Vector2D& velocity() const { return velocity_; }

    pyramidworks::collision::CollisionObject* collision_object() { return collision_object_; }

    void Die() { to_be_removed_ = true; }
    bool dead() const { return to_be_removed_; }

    GameScene* game_controller() { return game_controller_; }

    void set_timed_life(ugdk::time::TimeAccumulator* timed_life) { timed_life_ = timed_life; }

    void OnSceneAdd(GameScene* scene);

  private:
    component::Graphic*       graphic_component_;
    component::Controller* controller_component_;
    component::Damageable* damageable_component_;
    component::Physics*       physics_component_;
    
    ugdk::time::TimeAccumulator* timed_life_;
    ugdk::math::Vector2D world_position_;
    ugdk::math::Vector2D velocity_;
    pyramidworks::collision::CollisionObject* collision_object_;
    GameScene* game_controller_;
    bool to_be_removed_;
};

} // namespace game

#endif // TOPDOWN_GAME_GAMEOBJECT_H_