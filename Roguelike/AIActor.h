#pragma once
#include "AIChaseTargetComponent.h"
#include "Actor.h"
#include "PerceptionComponent.h"
#include "Vector.h"
namespace Roguelike {
/**
 * @brief Base class for AI controlled actors
 */
class AIActor : public Actor {
   public:
    struct Parameters {
        Actor::Parameters baseActorParameters;
        AIChaseTargetComponent::Parameters chaseTargetParameters = {0.0F, 0.0F};
        PerceptionComponent::Parameters perceptionParameters =
            PerceptionComponent::defaultParameters;
    };
    explicit AIActor(const Parameters& parameters,
                     const MaxrEngine::Vector2Df& position = {0.0F, 0.0F});
};

}  // namespace Roguelike