#pragma once
#include "Component.h"
#include "InputComponent.h"
#include "TransformComponent.h"

namespace MaxrEngine {
class MovementComponent : public Component {
   public:
    ENGINE_API MovementComponent(GameObject* gameObject);

    virtual void Update(float deltaTime) override;
    virtual void Render() override;

    ENGINE_API void SetSpeed(float newSpeed);
    ENGINE_API float GetSpeed() const;
    ENGINE_API float GetAccelerationSquared() const;

   private:
    InputComponent* input;
    TransformComponent* transform;

    float speed = 0.f;
    Vector2Df previosPosition = {0.f, 0.f};
    Vector2Df acceleration = {0.f, 0.f};
};
}  // namespace MaxrEngine
