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
#include "OffsetSpriteRendererComponent.h"
#include "SpriteAnimationComponent.h"
#include "Vector.h"

namespace Roguelike {
class ActorSave {
    /**
     * @brief Data structure for saving Actor state
     */
    friend class Actor;
    std::shared_ptr<HealthSave> healthSave;  ///< Saved health state
    std::shared_ptr<ArmorSave> armorSave;    ///< Saved armor state
    int actorGroupID = 0;                    ///< Actor's group identifier
};
/**
 * @brief Base class for all actor entities (player, enemies)
 * @details Constructs a GameObject with transform, rendering,
 * animation, physics, health, and combat components. Configurable through
 * the Parameters structure.
 */
class Actor : public GameObjectContainer, public ISaveable<Actor, ActorSave> {
   public:
    /**
     * @brief Configuration structure for Actor construction
     */
    struct Parameters {
        int actorGroupID;       ///< Group identifier for ActorRegisterSystem
        float maxHealthAmount;  ///< Maximum health points
        BarComponent::Parameters
            healthBarParameters;     ///< Health bar display settings
        float movementSpeed;         ///< Base actor movement speed
        MaxrEngine::Vector2Df size;  ///< Collision and render size
        OffsetSpriteRendererComponent::Parameters
            spriteOffsetParameters;  ///< Parameters for
                                     ///< OffsetSpriteRendererComponent
        std::string
            defaultAnimationName;  ///< Animation name that is used by default
        std::unordered_map<std::string, MaxrEngine::Animation>
            animations;  ///< Available animations
        bool haveBlock;  ///< Whether actor can block attack
        BlockComponent::Parameters
            blockParameters;  ///< Blocking component settings
        bool haveArmor;       ///< Whether actor has armor
        ArmorComponent::Parameters
            armorParameters;  ///< Armor component settings
        BarComponent::Parameters
            armorBarParameters;  ///< Armor bar display settings
        AttackComponent::Parameters
            attackComponentParameters;    ///< Attack component settings
        std::string actorName = "Actor";  ///< Name used for created GameObject
    };
    /**
     * @brief Constructs an Actor with specified parameters
     * @param parameters Configuration settings for the actor
     * @param position Initial world position
     */
    explicit Actor(const Parameters& parameters,
                   const MaxrEngine::Vector2Df& position = {0.0F, 0.0F});

   private:
    friend class ISaveable<Actor, ActorSave>;
    /**
     * @brief Saves actor state to save structure
     * @param save Shared pointer to save structure
     */
    void SaveImpl(std::shared_ptr<ActorSave> save) const;
    /**
     * @brief Loads actor state from save structure
     * @param save Shared pointer to save structure
     */
    void LoadImpl(std::shared_ptr<const ActorSave> save);
};
}  // namespace Roguelike
