#pragma once

#include "GameObject.h"
#include "InputComponent.h"

namespace Roguelike {
class KeyboardInputComponent : public MaxrEngine::InputComponent {
   public:
    explicit KeyboardInputComponent(MaxrEngine::GameObject* gameObject);

    void Update(float deltaTime) override;
};
}  // namespace Roguelike
