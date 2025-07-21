#pragma once
#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "IObserver.h"
namespace Roguelike {
class AITargetSelector : public MaxrEngine::Component,
                         virtual public MaxrEngine::IObservable,
                         virtual public MaxrEngine::IObserver {
   public:
    explicit AITargetSelector(MaxrEngine::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;
    void UpdateTarget();
    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;
};
}  // namespace Roguelike
