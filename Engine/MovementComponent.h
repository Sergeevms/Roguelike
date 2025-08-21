#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace MaxrEngine {
class MovementComponent : public Component {
   public:
    explicit MovementComponent(GameObject* gameObject);
    MovementComponent(GameObject* gameObject, const float speed);

    void Update(float deltaTime) override;

    void SetSpeed(float newSpeed);
    float GetSpeed() const;
    float GetAccelerationSquared() const;

   private:
    TransformComponent* transform;

    float speed = 0.0F;
    Vector2Df previosPosition = {0.0F, 0.0F};
    Vector2Df acceleration = {0.0F, 0.0F};
};
}  // namespace MaxrEngine
