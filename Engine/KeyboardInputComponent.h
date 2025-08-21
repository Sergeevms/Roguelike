#pragma once

#include "GameObject.h"
#include "InputComponent.h"

namespace MaxrEngine {
class KeyboardInputComponent : public InputComponent {
   public:
    explicit KeyboardInputComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
};
}  // namespace MaxrEngine
