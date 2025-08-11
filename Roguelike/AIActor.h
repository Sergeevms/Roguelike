#pragma once
#include "AIChaseTargetComponent.h"
#include "Actor.h"
#include "PerceptionComponent.h"
#include "Vector.h"
namespace Roguelike {
/**
 * @brief Base class for AI controlled actors
 * @details Class constructing GameObject with TransformComponent,
 * ActorComponent, HealthComponent, HealthBarComponent, SpriteRendererComponent,
 * SpriteAnimationComponent, ActorSpriteDirectionComponent,
 * ActorMovementComponent, RigidBodyComponent, SpriteColliderComponent,
 * AIInputComponent, AIChaseTargetComponent, AIBlackboard,
 * AIPerceptionComponent, PerceptionComponentDebugDraw, AITargetSelector,
 * AIAttackComponent, optional BlockComponent, ArmorComponent and
 * ArmorBarComponent.
 */
class AIActor : public Actor {
   public:
    friend class AIActorSpawnManager;
    struct Parameters {
        Actor::Parameters baseActorParameters;
        AIChaseTargetComponent::Parameters chaseTargetParameters = {0.0F, 0.0F};
        PerceptionComponent::Parameters perceptionParameters =
            PerceptionComponent::defaultParameters;
    };

   private:
    explicit AIActor(const Parameters& parameters,
                     const MaxrEngine::Vector2Df& position = {0.0F, 0.0F});
};

}  // namespace Roguelike