
#include "game/component/playercontroller.h"

#include "game/gameobject.h"
#include "game/gamescene.h"
#include "game/builder/objectbuilder.h"

#include <ugdk/graphic/module.h>
#include <ugdk/graphic/rendertarget.h>
#include <ugdk/input/module.h>
#include <ugdk/input/scancode.h>
#include <ugdk/time/timeaccumulator.h>


namespace game {
namespace component {
 
using namespace ugdk;
const double PlayerController::VELOCITY = 100.0;

PlayerController::PlayerController(const builder::ObjectBuilder& builder)
    : fire_cooldown_(new ugdk::time::TimeAccumulator(300))
    , builder_(builder) {}

PlayerController::~PlayerController() {}

void PlayerController::Update(double dt, GameObject* owner) {
    const auto& keyboard = input::manager()->keyboard();

    math::Vector2D velocity;

    if (keyboard.IsDown(input::Scancode::RIGHT) || keyboard.IsDown(input::Scancode::D))
        velocity.x += VELOCITY;
    if (keyboard.IsDown(input::Scancode::LEFT) || keyboard.IsDown(input::Scancode::A))
        velocity.x -= VELOCITY;
    if (keyboard.IsDown(input::Scancode::UP) || keyboard.IsDown(input::Scancode::W))
        velocity.y -= VELOCITY;
    if (keyboard.IsDown(input::Scancode::DOWN) || keyboard.IsDown(input::Scancode::S))
        velocity.y += VELOCITY;

    owner->set_velocity(velocity);

    const auto& mouse = input::manager()->mouse();

    if (mouse.IsDown(input::MouseButton::LEFT) && fire_cooldown_->Expired()) {
        ugdk::math::Vector2D direction = mouse.position() - graphic::manager()->screen()->size() * 0.5;
        
        auto proj = builder_.BuildProjectile(direction.Normalize(), 400);
        proj->set_world_position(owner->world_position());
        owner->game_controller()->QueuedAddEntity(proj);

        fire_cooldown_->Restart();
    }
}

} // namespace component
} // namespace game