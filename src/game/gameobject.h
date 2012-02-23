#ifndef TOPDOWN_GAME_GAMEOBJECT_H_
#define TOPDOWN_GAME_GAMEOBJECT_H_

#include <ugdk/action/entity.h>
#include "game/component.h"

namespace game {

class GameObject : public ugdk::Entity {
  typedef ugdk::Entity super;
  public:
    GameObject(component::Graphic* graphic, component::Controller* controller);
    ~GameObject();

    void Update(double dt);

    component::Graphic*       graphic_component() { return    graphic_component_; }
    component::Controller* controller_component() { return controller_component_; }

private:
    component::Graphic*       graphic_component_;
    component::Controller* controller_component_;
};

} // namespace game

#endif // TOPDOWN_GAME_GAMEOBJECT_H_