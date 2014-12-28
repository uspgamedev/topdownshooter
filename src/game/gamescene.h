#ifndef TOPDOWN_GAME_GAMESCENE_H_
#define TOPDOWN_GAME_GAMESCENE_H_

#include <ugdk/action/scene.h>

#include "game.h"

#include <ugdk/ui.h>
#include <ugdk/time.h>
#include <pyramidworks/collision.h>

#include <memory>

namespace game {

class GameScene : public ugdk::action::Scene {
public:
    GameScene(int time_left, std::unique_ptr<pyramidworks::collision::CollisionManager>);

    std::shared_ptr<ugdk::ui::Node> content_node() { return content_node_; }
    pyramidworks::collision::CollisionManager* collision() { return collision_.get(); }

    void QueuedAddEntity(const std::shared_ptr<GameObject>& obj);

private:
    std::unique_ptr<ugdk::time::TimeAccumulator> time_left_;
    std::unique_ptr<pyramidworks::collision::CollisionManager> collision_;
    std::shared_ptr<ugdk::ui::Node> content_node_;
    std::list<std::shared_ptr<GameObject>> objects_, queued_objects_;
};

} // namespace game

#endif // TOPDOWN_GAME_GAMESCENE_H_