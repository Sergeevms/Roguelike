#pragma once
#include "Component.h"
#include "EngineAPI.h"
#include "IObserver.h"

namespace MaxrEngine {
class InputComponent : public Component, public IObservable {
   public:
    explicit ENGINE_API InputComponent(GameObject* gameObject);

    ENGINE_API void Update(float deltaTime) override = 0;
    ENGINE_API void Render() override;

    ENGINE_API float GetHorizontalAxis() const;
    ENGINE_API float GetVerticalAxis() const;
    ENGINE_API bool getAttack() const;
    ENGINE_API bool getBlock() const;
    ENGINE_API bool getLevelTransfer() const;

   protected:
    float horizontalAxis = 0.0F;
    float verticalAxis = 0.0F;
    bool attack = false;
    bool block = false;
    bool levelTransfer = false;
};
}  // namespace MaxrEngine
