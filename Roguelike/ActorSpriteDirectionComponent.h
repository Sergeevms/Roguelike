#pragma once
#include <memory>

#include "GameObject.h"
#include "HealthComponent.h"
#include "SpriteDirectionComponent.h"
namespace Roguelike {
class ActorSpriteDirectionComponent
    : public MaxrEngine::SpriteDirectionComponent {
   public:
    explicit ActorSpriteDirectionComponent(MaxrEngine::GameObject* gameObject);
    void Update(float deltaTime) override;

   private:
    std::weak_ptr<HealthComponent> healthComponentPtr;
};
}  // namespace Roguelike
