#pragma once
#include "EngineAPI.h"
#include "GameObject.h"
#include "InputComponent.h"

namespace MaxrEngine {
class KeyboardInputComponent : public InputComponent {
   public:
    explicit ENGINE_API KeyboardInputComponent(GameObject* gameObject);

    ENGINE_API void Update(float deltaTime) override;
};
}  // namespace MaxrEngine
