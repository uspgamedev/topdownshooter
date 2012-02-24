#include <ugdk/base/engine.h>
#include <ugdk/input/inputmanager.h>
#include <ugdk/input/keys.h>

#include "game/component/controller.h"

#include "game/gameobject.h"

namespace game {
namespace component {

const double Controller::VELOCITY = 100.0;

void Controller::Update(double dt, GameObject* owner) {
    ugdk::input::InputManager* input = INPUT_MANAGER();

    ugdk::Vector2D& position = owner->world_position();

    if(input->KeyDown(ugdk::input::K_RIGHT))
        position.x += VELOCITY * dt;
    if(input->KeyDown(ugdk::input::K_LEFT))
        position.x -= VELOCITY * dt;
    if(input->KeyDown(ugdk::input::K_UP))
        position.y -= VELOCITY * dt;
    if(input->KeyDown(ugdk::input::K_DOWN))
        position.y += VELOCITY * dt;
}

} // namespace component
} // namespace game