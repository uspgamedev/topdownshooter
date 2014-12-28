
#include "game/gamescene.h"

#include "game/gameobject.h"
#include <ugdk/time/timeaccumulator.h>
#include <ugdk/ui/node.h>
#include <pyramidworks/collision/collisionmanager.h>

#include <functional>

namespace game {

using namespace std::placeholders;
using namespace ugdk;
using std::bind;
using ugdk::action::Scene;

GameScene::GameScene(int time_left, std::unique_ptr<pyramidworks::collision::CollisionManager> colmanager)
    : time_left_(new time::TimeAccumulator(time_left))
    , content_node_(new ui::Node)
    , collision_(std::move(colmanager))
{
    AddTask([this](double dt) -> bool {
        if (time_left_->Expired()) {
            Finish();
            return true;
        }
        return false;
    });
    AddTask(system::Task([this](double dt) {
        objects_.remove_if([](const std::shared_ptr<GameObject>& obj) {
            return obj->dead();
        });
        for (const auto& obj : queued_objects_)
            obj->OnSceneAdd(this);
        objects_.splice(objects_.end(), queued_objects_);
    }, 0.9));
    AddTask([this](double dt) {
        for (const auto& obj : objects_)
            obj->Update(dt);
    });
    set_render_function(bind(&ui::Node::Render, content_node_.get(), _1));
}

void GameScene::QueuedAddEntity(const std::shared_ptr<GameObject>& obj) {
    queued_objects_.push_back(obj);
}


} // namespace game