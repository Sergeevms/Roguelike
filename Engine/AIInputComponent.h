#pragma once

#include "GameObject.h"
#include "InputComponent.h"
#include "Vector.h"
namespace MaxrEngine {
class AIInputComponent : public InputComponent {
   public:
    explicit AIInputComponent(GameObject* gameObject);

    void Update(float deltaTime) override;

    void SetDirection(const Vector2Df& newDirection);
    Vector2Df GetDirection() const;
};
}  // namespace MaxrEngine
