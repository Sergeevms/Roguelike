#pragma once
#include "InputComponent.h"
namespace MaxrEngine {
class KeyboardInputComponent : public InputComponent {
   public:
    ENGINE_API KeyboardInputComponent(GameObject* gameObject);

    ENGINE_API void Update(float deltaTime) override;
};
}  // namespace MaxrEngine
