#pragma once
#include <memory>

#include "AttackComponent.h"
#include "GameObject.h"
namespace Roguelike {
class AIAttackComponent : public AttackComponent {
   public:
    explicit AIAttackComponent(
        MaxrEngine::GameObject* gameObject,
        const Parameters& atackParameters = defaultParameters,
        std::weak_ptr<MaxrEngine::GameObject> target =
            std::weak_ptr<MaxrEngine::GameObject>());
    void Update(float deltaTime) override;
};
}  // namespace Roguelike
