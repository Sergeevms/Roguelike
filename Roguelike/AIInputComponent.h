#pragma once

#include "GameObject.h"
#include "InputComponent.h"
#include "Vector.h"
namespace Roguelike {
class AIInputComponent : public MaxrEngine::InputComponent {
   public:
    explicit AIInputComponent(MaxrEngine::GameObject* gameObject);

    void Update(float deltaTime) override;

    void SetDirection(const MaxrEngine::Vector2Df& newDirection);
    MaxrEngine::Vector2Df GetDirection() const;
};
}  // namespace Roguelike
