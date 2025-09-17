#include "AISpriteDirectionComponent.h"

#include "AIPerceptionComponent.h"
#include "ActorSpriteDirectionComponent.h"
#include "GameObject.h"
#include "SpriteRendererComponent.h"

namespace Roguelike {
AISpriteDirectionComponent::AISpriteDirectionComponent(
    MaxrEngine::GameObject* gameObject)
    : ActorSpriteDirectionComponent(gameObject) {
    perceptionPointer =
        gameObject->GetComponentSharedPtr<AIPerceptionComponent>();
}
void AISpriteDirectionComponent::Update(float deltaTime) {
    auto health = healthComponentPtr.lock();
    if (health && health->IsAlive()) {
        const auto perception = perceptionPointer.lock();
        auto renderer = rendererPointer.lock();
        if (perception && renderer) {
            const auto& direction = perception->GetVisionDirection();
            if (direction.x > 0) {
                renderer->FlipX(true ^ renderer->IsTextureRightDirected());
            } else if (direction.x < 0) {
                renderer->FlipX(false ^ renderer->IsTextureRightDirected());
            }
        } else {
            rendererPointer = gameObject->GetComponentSharedPtr<
                MaxrEngine::SpriteRendererComponent>();
            perceptionPointer =
                gameObject->GetComponentSharedPtr<AIPerceptionComponent>();
        }
    }
}
}  // namespace Roguelike