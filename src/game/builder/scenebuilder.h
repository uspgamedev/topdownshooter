#ifndef TOPDOWN_GAME_BUILDER_SCENEBUILDER_H_
#define TOPDOWN_GAME_BUILDER_SCENEBUILDER_H_

#include <ugdk/action.h>
#include <memory>

namespace game {
namespace builder {
namespace SceneBuilder {

std::unique_ptr<ugdk::action::Scene> BuildRandomScene();

}

} // namespace builder
} // namespace game

#endif // TOPDOWN_GAME_BUILDER_SCENEBUILDER_H_