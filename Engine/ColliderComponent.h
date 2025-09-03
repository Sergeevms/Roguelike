#pragma once
#include <functional>
#include <vector>

#include "SFML/Graphics/Rect.hpp"

#include "Collision.h"
#include "Component.h"
#include "Trigger.h"

namespace MaxrEngine {
/**
 * @brief Base class for all collision components providing common collision
 * detection infrastructure.
 * @details Automatically subscribes to the PhysicsSystem upon creation and
 * unsubscribes on destruction. Handles both solid collisions and trigger events
 * through subscription-based callbacks.
 */
class ColliderComponent : public Component {
   public:
    friend class PhysicsSystem;
    friend class ColliderDebugRender;

    explicit ColliderComponent(GameObject* gameObject);
    ~ColliderComponent();

    void Update(float deltaTime) override = 0;
    /**
     * @brief Sets whether this collider acts as a trigger.
     * @param newIsTrigger True for trigger (no physical response), false for
     * solid collider.
     */
    void SetTrigger(bool newIsTrigger);

    // Event subscription methods

    void SubscribeCollision(std::function<void(Collision)> onCollisionAction);
    void UnsubscribeCollision(std::function<void(Collision)> onCollisionAction);

    void SubscribeTriggerEntered(std::function<void(Trigger)> onTriggerEntered);
    void UnsubscribeTriggerEntered(
        std::function<void(Trigger)> onTriggerEntered);

    void SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExit);
    void UnsubscribeTriggerExit(std::function<void(Trigger)> onTriggerExit);

   protected:
    /**
     * @brief The axis-aligned bounding box of the collider in world
     * coordinates.
     */
    sf::FloatRect bounds;
    /**
     * @brief Flag marking collider as trigger
     * @details If true, this collider will not cause physical collisions and
     * call OnTriggerEntered/OntriggerExit methods on non-trigger colliders
     * entering/exiting trigger bounds.
     */
    bool isTrigger = false;

    // Event invocation methods

    void OnCollision(Collision collision);
    void OnTriggerEntered(Trigger trigger);
    void OnTriggerExit(Trigger trigger);

    // Subscriber lists for collision and trigger events

    std::vector<std::function<void(Collision)>> onCollisionActions;
    std::vector<std::function<void(Trigger)>> onTriggerEnteredActions;
    std::vector<std::function<void(Trigger)>> onTriggerExitActions;
};
}  // namespace MaxrEngine
