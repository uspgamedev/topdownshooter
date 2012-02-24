#ifndef TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_
#define TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_

#include "game.h"

namespace game {
namespace builder {

class ObjectBuilder {
  public:
    ObjectBuilder() {}
    ~ObjectBuilder() {}

    GameObject* BuildHero();
};

} // namespace builder
} // namespace game

#endif // TOPDOWN_GAME_BUILDER_OBJECTBUILDER_H_