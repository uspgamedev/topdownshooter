#include <ugdk/ui/node.h>

#include "game/component/graphic.h"

#include "game/gameobject.h"

namespace game {
namespace component {

Graphic::Graphic() : node_(new ugdk::ui::Node) {}

Graphic::~Graphic() {
    if (node_->parent())
        node_->parent()->RemoveChild(node_.get());
}

void Graphic::Update(double dt, GameObject* owner) {
    node_->geometry().set_offset(owner->world_position());
}

} // namespace component
} // namespace game