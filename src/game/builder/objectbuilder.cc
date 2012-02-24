#include <ugdk/base/engine.h>
#include <ugdk/graphic/node.h>
#include <ugdk/graphic/drawable/solidrectangle.h>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/math/vector2D.h>

#include "game/builder/objectbuilder.h"

#include "game/gameobject.h"
#include "game/component/graphic.h"
#include "game/component/controller.h"

namespace game {
namespace builder {

GameObject* ObjectBuilder::BuildHero() {
    GameObject* hero = new GameObject(new component::Graphic, new component::Controller);

    ugdk::graphic::SolidRectangle* hero_graphic = new ugdk::graphic::SolidRectangle(ugdk::Vector2D(15.0, 15.0));
    hero_graphic->set_color(ugdk::Color(0.25, 1.0, 0.25));
    hero_graphic->set_hotspot(ugdk::graphic::Drawable::CENTER);
    hero->graphic_component()->node()->set_drawable(hero_graphic);

    return hero;
}

} // namespace builder
} // namespace game