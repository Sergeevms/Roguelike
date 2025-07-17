#pragma once
#include "Component.h"
#include "EngineAPI.h"
#include "IObserver.h"

namespace MaxrEngine {
class InputComponent : public Component, public IObservable {
   public:
    ENGINE_API InputComponent(GameObject* gameObject);

    ENGINE_API virtual void Update(float deltaTime) = 0;
    ENGINE_API virtual void Render() override;

    ENGINE_API float GetHorizontalAxis() const;
    ENGINE_API float GetVerticalAxis() const;
    ENGINE_API bool getAttack() const;

   protected:
    float horizontalAxis = 0.0F;
    float verticalAxis = 0.0F;
    bool attack = false;
};
}  // namespace MaxrEngine
