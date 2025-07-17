#include "pch.h"

#include "SpriteRendererComponent.h"

#include "GameObject.h"
#include "RenderSystem.h"

namespace MaxrEngine {
SpriteRendererComponent::SpriteRendererComponent(GameObject* gameObject)
    : Component(gameObject) {
    sprite = new sf::Sprite();
    scale = {1, -1};
    sprite->setScale({1, -1});
    transform = gameObject->GetComponent<TransformComponent>();
}

SpriteRendererComponent::~SpriteRendererComponent() {
    if (sprite) {
        delete sprite;
    }
}

void SpriteRendererComponent::Update(float deltaTime) {}

void SpriteRendererComponent::Render() {
    if (sprite) {
        sprite->setPosition(
            Convert<sf::Vector2f, Vector2Df>(transform->GetWorldPosition()));
        sprite->setRotation(transform->GetWorldRotation());
        sprite->setScale(Convert<sf::Vector2f, Vector2Df>(
            scale * transform->GetWorldScale()));
        RenderSystem::Instance()->Render(*sprite);
    }
}

const sf::Sprite* SpriteRendererComponent::GetSprite() const { return sprite; }

void SpriteRendererComponent::SetTexture(const sf::Texture& newTexture) {
    sprite->setTexture(newTexture);
    auto textureSize = sprite->getTexture()->getSize();
    sprite->setOrigin({0.5f * textureSize.x, 0.5f * textureSize.y});
}

void SpriteRendererComponent::SetPixelSize(int newWidth, int newHeight) {
    auto originalSize = sprite->getTexture()->getSize();
    scale = {
        static_cast<float>(newWidth) / static_cast<float>(originalSize.x),
        -static_cast<float>(newHeight) / static_cast<float>(originalSize.y)};
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