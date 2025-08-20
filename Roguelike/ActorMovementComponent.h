#pragma once
#include <memory>

#include "GameObject.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
namespace Roguelike {
/**
 * \brief MovementComponent for Actors.
 * Moves only if actor is alive
 */
class ActorMovementComponent : public MaxrEngine::MovementComponent {
   public:
    explicit ActorMovementComponent(MaxrEngine::GameObject* gameObject,
                                    const float speed = 0.0F);
    void Update(float deltaTime) override;

   private:
    std::weak_ptr<HealthComponent> healtComponentPtr;
};
}  // namespace Roguelike
