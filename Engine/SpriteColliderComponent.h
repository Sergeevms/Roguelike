#pragma once
#include "SFML/Graphics/Sprite.hpp"

#include "ColliderComponent.h"
#include "GameObject.h"

namespace MaxrEngine {
/**
 * @brief A ColliderComponent that automatically fits its bounds to the
 * associated sprite's global bounds.
 * @details This component requires a SpriteRendererComponent on the same
 * GameObject to function. It dynamically updates its collision bounds every
 * frame to match the sprite's current size and position.
 */
class SpriteColliderComponent : public ColliderComponent {
   public:
    explicit SpriteColliderComponent(GameObject* gameObject);
    ~SpriteColliderComponent();
    /**
     * @brief Updates collision bounds to match the sprite's current size and
     * position.
     * @param deltaTime - unused parameter in inhereted method from Component.
     */
    void Update(float deltaTime) override;

   private:
    /**
     * @brief Non-owning pointer to the sprite from a SpriteRendererComponent.
     */
    const sf::Sprite* sprite;
};
}  // namespace MaxrEngine
