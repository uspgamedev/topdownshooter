
#include <ugdk/system/engine.h>
#include <ugdk/system/configuration.h>

#include "game/builder/scenebuilder.h"
#include <ugdk/action/scene.h>

using namespace ugdk;

int main(int argc, char **argv) {
    system::Configuration engine_config;
    engine_config.windows_list[0].title = "Top-down shooter";
    engine_config.windows_list[0].fullscreen = false;

    system::Initialize(engine_config);

    system::PushSceneFactory(game::builder::SceneBuilder::BuildRandomScene);

    system::Run();
    system::Release();
    return 0;
}