#include <cstdlib>
#include "game/component/physics.h"
#include "game/gameobject.h"

namespace game {
namespace component {

#define PI 3.1415926535897932384626433832795

Physics::Physics(const ugdk::math::Vector2D& bounds) : bounds_(bounds) {}

Physics::~Physics() {
}

void Physics::Update(double dt, GameObject* owner) {
    ugdk::math::Vector2D map_size = bounds_;
    ugdk::math::Vector2D next_position = owner->world_position() + owner->velocity() * dt;

    if(next_position.x < 0) next_position.x = 0;
    if(next_position.y < 0) next_position.y = 0;
    if(next_position.x > map_size.x) next_position.x = map_size.x;
    if(next_position.y > map_size.y) next_position.y = map_size.y;

    owner->set_world_position(next_position);
}

} // namespace component
} // namespace game