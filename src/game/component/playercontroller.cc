#include <ugdk/base/engine.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/input/inputmanager.h>
#include <ugdk/input/keys.h>
#include <ugdk/time/timeaccumulator.h>

#include "game/component/playercontroller.h"

#include "game/gameobject.h"
#include "game/gamecontroller.h"
#include "game/builder/objectbuilder.h"

namespace game {
namespace component {

const double PlayerController::VELOCITY = 100.0;

PlayerController::PlayerController() : fire_cooldown_(new ugdk::time::TimeAccumulator(300)) {}
PlayerController::~PlayerController() { delete fire_cooldown_; }

void PlayerController::Update(double dt, GameObject* owner) {
    ugdk::input::InputManager* input = INPUT_MANAGER();

    ugdk::Vector2D velocity;

    if(input->KeyDown(ugdk::input::K_RIGHT) || input->KeyDown(ugdk::input::K_d))
        velocity.x += VELOCITY;
    if(input->KeyDown(ugdk::input::K_LEFT) || input->KeyDown(ugdk::input::K_a))
        velocity.x -= VELOCITY;
    if(input->KeyDown(ugdk::input::K_UP) || input->KeyDown(ugdk::input::K_w))
        velocity.y -= VELOCITY;
    if(input->KeyDown(ugdk::input::K_DOWN) || input->KeyDown(ugdk::input::K_s))
        velocity.y += VELOCITY;

    owner->set_velocity(velocity);

    if(input->MouseDown(ugdk::input::M_BUTTON_LEFT) && fire_cooldown_->Expired()) {
        ugdk::Vector2D direction = input->GetMousePosition() - VIDEO_MANAGER()->video_size() * 0.5;
        
        builder::ObjectBuilder build(owner->game_controller()->collision_manager());
        GameObject* proj = build.BuildProjectile(direction.Normalize(), 400);
        proj->set_world_position(owner->world_position());
        owner->game_controller()->AddGameObject(proj);

        fire_cooldown_->Restart();
    }
}

} // namespace component
} // namespace game