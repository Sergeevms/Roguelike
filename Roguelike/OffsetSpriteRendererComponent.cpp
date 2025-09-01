#include "OffsetSpriteRendererComponent.h"

#include "SFML/System/Vector2.hpp"

#include "GameObject.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"
#include "Vector.h"
namespace Roguelike {
OffsetSpriteRendererComponent::OffsetSpriteRendererComponent(
    MaxrEngine::GameObject* gameObject, const MaxrEngine::Vector2Df& offset,
    const int layer)
    : SpriteRendererComponent(gameObject, layer), offset(offset) {}
void OffsetSpriteRendererComponent::Render() {
    if (sprite != nullptr) {
        sprite->setPosition(
            Convert<sf::Vector2f>(transform->GetWorldPosition() + offset));
        sprite->setRotation(transform->GetWorldRotation());
        sprite->setScale(
            Convert<sf::Vector2f>(scale * transform->GetWorldScale()));
        MaxrEngine::RenderSystem::Instance()->Render(*sprite, layer);
    }
}
void OffsetSpriteRendererComponent::SetOffset(
    MaxrEngine::Vector2Df& newOffset) {
    offset = newOffset;
}
const MaxrEngine::Vector2Df& OffsetSpriteRendererComponent::GetOffset() const {
    return offset;
}
}  // namespace Roguelike
