#include "OffsetSpriteRendererComponent.h"

#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"

#include "GameObject.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"
#include "Vector.h"
namespace Roguelike {
OffsetSpriteRendererComponent::OffsetSpriteRendererComponent(
    MaxrEngine::GameObject* gameObject, const int layer)
    : SpriteRendererComponent(gameObject, layer) {}

void OffsetSpriteRendererComponent::SetTexture(
    const sf::Texture& newTexture, const Parameters& parameters,
    const bool newIsTextureRightDirected) {
    SpriteRendererComponent::SetTexture(newTexture, newIsTextureRightDirected);
    SetOffsetParameters(parameters);
}
void OffsetSpriteRendererComponent::Render() {
    if (sprite != nullptr) {
        auto currentOffset = offset * scale * coefficient;
        sprite->setPosition(Convert<sf::Vector2f>(
            transform->GetWorldPosition() + currentOffset));
        sprite->setRotation(transform->GetWorldRotation());
        sprite->setScale(Convert<sf::Vector2f>(scale * coefficient *
                                               transform->GetWorldScale()));
        MaxrEngine::RenderSystem::Instance()->Render(*sprite, layer);
    }
}
void OffsetSpriteRendererComponent::SetOffsetParameters(
    const Parameters& parameters) {
    const auto textureSize =
        Convert<Vector2Df>(parameters.originalSpriteTextureSize);
    const auto imageSize = Convert<Vector2Df>(parameters.originalImageSize);
    coefficient = {textureSize.x / imageSize.x, textureSize.y / imageSize.y};
    offset = Convert<Vector2Df>(parameters.originalCenterOffset);
}
void OffsetSpriteRendererComponent::FlipX(bool flip) {
    if (flip != isFlipX) {
        scale.x *= -1;
        offset.x *= -1;
        isFlipX = flip;
    }
}
void OffsetSpriteRendererComponent::FlipY(bool flip) {
    if (flip != isFlipY) {
        scale.y *= -1;
        offset.y *= -1;
        isFlipY = flip;
    }
}
}  // namespace Roguelike
