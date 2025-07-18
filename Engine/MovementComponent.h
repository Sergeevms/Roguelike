#pragma once
#include "Component.h"
#include "EngineAPI.h"
#include "InputComponent.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace MaxrEngine {
class MovementComponent : public Component {
   public:
    explicit ENGINE_API MovementComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    ENGINE_API void SetSpeed(float newSpeed);
    ENGINE_API float GetSpeed() const;
    ENGINE_API float GetAccelerationSquared() const;

   private:
    InputComponent* input;
    TransformComponent* transform;

    float speed = 0.0F;
    Vector2Df previosPosition = {0.0F, 0.0F};
    Vector2Df acceleration = {0.0F, 0.0F};
};
}  // namespace MaxrEngine
