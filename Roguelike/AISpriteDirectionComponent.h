#pragma once
#include <memory>

#include "AIPerceptionComponent.h"
#include "ActorSpriteDirectionComponent.h"
#include "GameObject.h"

namespace Roguelike {
class AISpriteDirectionComponent : public ActorSpriteDirectionComponent {
   public:
    explicit AISpriteDirectionComponent(MaxrEngine::GameObject* gameObject);
    void Update(float deltaTime) override;

   protected:
    std::weak_ptr<AIPerceptionComponent> perceptionPointer;
};
}  // namespace Roguelike
