#ifndef TOPDOWN_GAME_COMPONENT_DAMAGEABLE_H_
#define TOPDOWN_GAME_COMPONENT_DAMAGEABLE_H_

#include <ugdk/graphic.h>
#include "game.h"

namespace game {
namespace component {

class Damageable {
  //typedef ugdk::Scene super;
  public:
    Damageable(double max_life) : current_life_(max_life), max_life_(max_life) {}
    ~Damageable() {}

    void Update(double dt, GameObject* owner);

    void Damage(double damage) { current_life_ -= damage; }

    double current_life() const { return current_life_; }

  private:
    double current_life_;
    double max_life_;
};

} // namespace component
} // namespace game

#endif // TOPDOWN_GAME_COMPONENT_DAMAGEABLE_H_