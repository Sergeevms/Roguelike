#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "ArmorComponent.h"
#include "AttackComponent.h"
#include "BarComponent.h"
#include "BlockComponent.h"
#include "GameObjectContainer.h"
#include "HealthComponent.h"
#include "ISaveable.h"
#include "SpriteAnimationComponent.h"
#include "Vector.h"

namespace Roguelike {
class ActorSave {
    friend class Actor;
    std::shared_ptr<HealthSave> healthSave;
    std::shared_ptr<ArmorSave> armorSave;
    int actorGroupID = 0;
};
/**
 * \brief Base class for actors like player or enemy.
 * \details Class constructing GameObject with TransformComponent,
 * ActorComponent, HealthComponent, HealthBarComponent, MovementComponent,
 * RigidBodyComponent, SpriteRendererComponent, SpriteAnimationComponent,
 * SpriteColliderComponent, optional BlockComponent, ArmorComponent &
 * ArmorBarComponent. Parameters for components above are passed through
 * Actor::Parameters struct.
 */
class Actor : public GameObjectContainer, public ISaveable<Actor, ActorSave> {
   public:
    /**
     * \brief Struct storing parameters to build Actor
     */
    struct Parameters {
        int actorGroupID;
        float maxHealthAmount;
        BarComponent::Parameters healthBarParameters;
        float movementSpeed;
        MaxrEngine::Vector2Df size;
        MaxrEngine::Vector2Di imageSize;
        MaxrEngine::Vector2Di spriteSize;
        MaxrEngine::Vector2Df spriteOffset;
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

   private:
    friend class ISaveable<Actor, ActorSave>;
    void SaveImpl(std::shared_ptr<ActorSave> save) const;
    void LoadImpl(std::shared_ptr<const ActorSave> save);
};
}  // namespace Roguelike
