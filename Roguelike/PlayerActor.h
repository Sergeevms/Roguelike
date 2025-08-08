#pragma once
#include "Actor.h"
namespace Roguelike {
class PlayerActor : public Actor {
   public:
    PlayerActor(const Actor::Parameters& parameters,
                const MaxrEngine::Vector2Df& position = {0.0F, 0.0F});
};
}  // namespace Roguelike
