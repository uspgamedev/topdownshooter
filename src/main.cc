#include <ugdk/base/engine.h>
#include <pyramidworks/collision/collisionmanager.h>
#include "game/gamecontroller.h"

int main(int argc, char **argv) {
	ugdk::Engine::Configuration engine_config;
	engine_config.window_title = "Top-down shooter";
	engine_config.fullscreen   = false;

    ugdk::Engine* engine = ugdk::Engine::reference();
    engine->Initialize(engine_config);

    pyramidworks::collision::CollisionManager* collision = pyramidworks::collision::CollisionManager::reference();
    collision->Generate("Object");
    collision->Generate("Creature", "Object");
    collision->Generate("Hero", "Creature");
    collision->Generate("Enemy", "Creature");
    collision->Generate("Projectile", "Object");

    engine->PushScene(new game::GameController);

    engine->Run();
    engine->Release();
    return 0;
}