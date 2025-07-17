#pragma once
#include <functional>
#include <vector>

#include "SFML/Graphics.hpp"

#include "Collision.h"
#include "Component.h"
#include "PhysicsSystem.h"
#include "Trigger.h"

namespace MaxrEngine {
class ColliderComponent : public Component {
   public:
    friend class PhysicsSystem;

    ENGINE_API ColliderComponent(GameObject* gameObject);

    void Update(float deltaTime) override = 0;
    void Render() override = 0;

    ENGINE_API void SetTrigger(bool newIsTrigger);

    ENGINE_API void SubscribeCollision(
        std::function<void(Collision)> onCollisionAction);
    ENGINE_API void UnsubscribeCollision(
        std::function<void(Collision)> onCollisionAction);

    ENGINE_API void SubscribeTriggerEntered(
        std::function<void(Trigger)> onTriggerEntered);
    ENGINE_API void UnsubscribeTriggerEntered(
        std::function<void(Trigger)> onTriggerEntered);

    ENGINE_API void SubscribeTriggerExit(
        std::function<void(Trigger)> onTriggerExit);
    ENGINE_API void UnsubscribeTriggerExit(
        std::function<void(Trigger)> onTriggerExit);

   protected:
    sf::FloatRect bounds;
    bool isTrigger = false;

    void OnCollision(Collision collision);
    void OnTriggerEntered(Trigger trigger);
    void OnTriggerExit(Trigger trigger);

    std::vector<std::function<void(Collision)>> onCollisionActions;
    std::vector<std::function<void(Trigger)>> onTriggerEnteredActions;
    std::vector<std::function<void(Trigger)>> onTriggerExitActions;
};
}  // namespace MaxrEngine
