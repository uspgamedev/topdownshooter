#include <cstdlib>
#include "game/component/physics.h"

#include "game/gameobject.h"
#include "game/gamecontroller.h"

namespace game {
namespace component {

#define PI 3.1415926535897932384626433832795

Physics::Physics() {
}

Physics::~Physics() {
}

void Physics::Update(double dt, GameObject* owner) {
    GameController* controller = owner->game_controller();

    if(owner->world_position().x < 0.0 || owner->world_position().x >= controller->map_size().x)
        owner->velocity().x *= -1.0;
    if(owner->world_position().y < 0.0 || owner->world_position().y >= controller->map_size().y)
        owner->velocity().y *= -1.0;

    owner->set_world_position(owner->world_position() + owner->velocity() * dt);
}

} // namespace component
} // namespace game