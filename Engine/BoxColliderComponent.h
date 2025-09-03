#pragma once
#include "ColliderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Vector.h"
namespace MaxrEngine {
/**
 * @brief A ColliderComponent with manually defined rectangular bounds centered
 * on the GameObject's position.
 * @details The collider's size is set explicitly and remains constant unless
 * changed via SetSize(). The Transform's position represents the center of the
 * collider, not its top-left corner. Used for static objects, triggers, or
 * characters where the collision shape differs from the visual sprite.
 */
class BoxColliderComponent : public ColliderComponent {
   public:
    explicit BoxColliderComponent(GameObject* gameObject,
                                  const Vector2Df& size = {0.0F, 0.0F});
    /**
     * @brief Updates the collider's world position based on the Transform's
     * current position.
     */
    void Update(const float deltaTime) override;
    /**
     * @brief Sets the size of the collider and recalculates its world position.
     * @param newSize - The new dimensions (width, height) for the collider.
     */
    void SetSize(const Vector2Df& newSize);

   private:
    /**
     * @brief Recalculates the world position (top-left corner) of the bounds
     * based on the Transform's center position.
     */
    void UpdateBoundsPosition();
    /**
     * @brief Non-owning pointer to TransformComponent
     */
    const TransformComponent* transform;
};
}  // namespace MaxrEngine