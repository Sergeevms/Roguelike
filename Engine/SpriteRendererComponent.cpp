#include "pch.h"

#include "SpriteRendererComponent.h"

#include "SFML/Graphics/Sprite.hpp"

#include "Component.h"
#include "GameObject.h"
#include "RenderSystem.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace MaxrEngine {
SpriteRendererComponent::SpriteRendererComponent(GameObject* gameObject)
    : Component(gameObject) {
    sprite = new sf::Sprite();
    scale = {1, -1};
    sprite->setScale({1, -1});
    transform = gameObject->GetComponent<TransformComponent>();
}

SpriteRendererComponent::~SpriteRendererComponent() { delete sprite; }

void SpriteRendererComponent::Update(float deltaTime) {}

void SpriteRendererComponent::Render() {
    if (sprite != nullptr) {
        sprite->setPosition(
            Convert<sf::Vector2f>(transform->GetWorldPosition()));
        sprite->setRotation(transform->GetWorldRotation());
        sprite->setScale(
            Convert<sf::Vector2f>(scale * transform->GetWorldScale()));
        RenderSystem::Instance()->Render(*sprite);
    }
}

const sf::Sprite* SpriteRendererComponent::GetSprite() const { return sprite; }

void MaxrEngine::SpriteRendererComponent::SetTexture(
    const sf::Texture& newTexture, const bool newIsTextureRightDirected) {
    sprite->setTexture(newTexture);
    auto textureSize = Convert<sf::Vector2f>(sprite->getTexture()->getSize());
    constexpr float half = 0.5F;
    const sf::Vector2f textureCenter = {half * textureSize.x,
                                        half * textureSize.y};
    sprite->setOrigin(textureCenter);
    isTextureRightDirected = newIsTextureRightDirected;
}

void SpriteRendererComponent::SetPixelSize(const Vector2Di& size) {
    SetPixelSize(size.x, size.y);
}

void SpriteRendererComponent::SetPixelSize(int newWidth, int newHeight) {
    auto originalSize = Convert<sf::Vector2f>(sprite->getTexture()->getSize());
    scale = {static_cast<float>(newWidth) / originalSize.x,
             -static_cast<float>(newHeight) / originalSize.y};
}

bool SpriteRendererComponent::IsTextureRightDirected() const {
    return isTextureRightDirected;
}

ENGINE_API void SpriteRendererComponent::SetColor(const sf::Color newColor) {
    sprite->setColor(newColor);
}

void SpriteRendererComponent::FlipX(bool flip) {
    if (flip != isFlipX) {
        scale.x *= -1;
        isFlipX = flip;
    }
}

void SpriteRendererComponent::FlipY(bool flip) {
    if (flip != isFlipY) {
        scale.y *= -1;
        isFlipY = flip;
    }
}
}  // namespace MaxrEngine