#pragma once
#include <string>
#include <unordered_map>

#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "BarComponent.h"
#include "BlockComponent.h"
#include "GameObjectContainer.h"
#include "SpriteAnimationComponent.h"
#include "Vector.h"

namespace Roguelike {
/**
 * \brief Base class for actors like player or enemy.
 * \details Class constructing GameObject with TransformComponent,
 * ActorComponent, HealthComponent, HealthBarComponent, MovementComponent,
 * RigidBodyComponent, SpriteRendererComponent, SpriteAnimationComponent,
 * SpriteColliderComponent, optional BlockComponent, ArmorComponent &
 * ArmorBarComponent. Parameters for components above are passed through
 * Actor::Parameters struct.
 */
class Actor : public GameObjectContainer {
   public:
    /**
     * \brief Struct storing parameters to build Actor
     */
    struct Parameters {
        int actorGroupID;
        float maxHealthAmount;
        BarComponent::Parameters healthBarParameters;
        float movementSpeed;
        MaxrEngine::Vector2Di spriteSize;
        std::string defaultAnimationName;
        std::unordered_map<std::string, MaxrEngine::Animation> animations;
        bool haveBlock;
        BlockComponent::Parameters blockParameters;
        bool haveArmor;
        ArmorComponent::Parameters armorParameters;
        BarComponent::Parameters armorBarParameters;
        AttackComponent::Parameters attackComponentParameters;
        std::string actorName = "Actor";
    };
    explicit Actor(const Parameters& parameters,
                   const MaxrEngine::Vector2Df& position = {0.0F, 0.0F});
};
}  // namespace Roguelike
