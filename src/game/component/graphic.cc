#include <ugdk/graphic/node.h>

#include "game/component/graphic.h"

#include "game/gameobject.h"

namespace game {
namespace component {

Graphic::Graphic() : node_(new ugdk::graphic::Node) {}

Graphic::~Graphic() {
    delete node_;
}

void Graphic::Update(double dt, GameObject* owner) {
    node_->modifier()->set_offset(owner->world_position());
}

} // namespace component
} // namespace game