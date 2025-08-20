#pragma once
#include "EngineAPI.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "Vector.h"
namespace MaxrEngine {
class AIInputComponent : public InputComponent {
   public:
    explicit ENGINE_API AIInputComponent(GameObject* gameObject);

    ENGINE_API void Update(float deltaTime) override;

    ENGINE_API void SetDirection(const Vector2Df& newDirection);
    ENGINE_API Vector2Df GetDirection() const;
};
}  // namespace MaxrEngine
