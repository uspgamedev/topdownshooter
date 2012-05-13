#ifndef TOPDOWN_GAME_BUILDER_SCENEBUILDER_H_
#define TOPDOWN_GAME_BUILDER_SCENEBUILDER_H_

#include <ugdk/action/scene.h>

namespace game {
namespace builder {

class SceneBuilder {
  public:
    SceneBuilder() {}
    ~SceneBuilder() {}

    ugdk::action::Scene* BuildRandomScene();
};

} // namespace builder
} // namespace game

#endif // TOPDOWN_GAME_BUILDER_SCENEBUILDER_H_