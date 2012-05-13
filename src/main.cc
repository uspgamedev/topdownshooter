#include <ugdk/base/engine.h>
#include "game/gamecontroller.h"

int main(int argc, char **argv) {
    ugdk::Configuration engine_config;
    engine_config.window_title = "Top-down shooter";
    engine_config.fullscreen   = false;

    ugdk::Engine* engine = ugdk::Engine::reference();
    engine->Initialize(engine_config);

    engine->PushScene(new game::GameController);

    engine->Run();
    engine->Release();
    return 0;
}