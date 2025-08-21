#pragma once
#include "Component.h"
#include "IObserver.h"

namespace MaxrEngine {
class InputComponent : public Component, public IObservable {
   public:
    explicit InputComponent(GameObject* gameObject);

    void Update(float deltaTime) override = 0;

    float GetHorizontalAxis() const;
    float GetVerticalAxis() const;
    bool getAttack() const;
    bool getBlock() const;

   protected:
    float horizontalAxis = 0.0F;
    float verticalAxis = 0.0F;
    bool attack = false;
    bool block = false;
};
}  // namespace MaxrEngine
