#pragma once
#include <memory>

#include "ColliderComponent.h"
#include "Component.h"
#include "GameObject.h"
#include "IRenderable.h"
namespace MaxrEngine {
/**
 * @brief A debug visualization component that draws the bounds of a
 * ColliderComponent.
 * @details Renders a white outline showing the collider's current bounds.
 * Automatically removes itself from the GameObject if the associated collider
 * is destroyed.
 */
class ColliderDebugRender : public Component, public IRenderable {
   public:
    explicit ColliderDebugRender(GameObject*,
                                 std::shared_ptr<ColliderComponent> collider,
                                 const int layer = 0);

    void Update(float deltaTime) override;
    /**
     * @brief Renders the collider bounds outline for debugging purposes.
     */
    void Render() override;

   private:
    /**
     * @brief Weak reference to the collider being visualized.
     */
    std::weak_ptr<ColliderComponent> colliderPtr;
};
}  // namespace MaxrEngine