#include <ugdk/base/engine.h>
#include "game/builder/scenebuilder.h"

int main(int argc, char **argv) {
    ugdk::Configuration engine_config;
    engine_config.window_title = "Top-down shooter";
    engine_config.fullscreen   = false;

    ugdk::Engine* engine = ugdk::Engine::reference();
    engine->Initialize(engine_config);

    game::builder::SceneBuilder builder;
    engine->PushScene(builder.BuildRandomScene());

    engine->Run();
    engine->Release();
    return 0;
}