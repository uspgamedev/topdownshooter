#include "game/gameobject.h"
#include "game/component/graphic.h"
#include "game/component/controller.h"

namespace game {

GameObject::GameObject(component::Graphic* graphic, component::Controller* controller)
  : graphic_component_(graphic),
    controller_component_(controller) {
}

GameObject::~GameObject() {
    delete graphic_component_;
    delete controller_component_;
}

void GameObject::Update(double dt) {
    graphic_component_->Update(dt);
    controller_component_->Update(dt);
}

} // namespace game