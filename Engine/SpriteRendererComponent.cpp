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

SpriteRendererComponent::~SpriteRendererComponent() {
    if (sprite != nullptr) {
        delete sprite;
    }
}

void SpriteRendererComponent::Update(float deltaTime) {}

void SpriteRendererComponent::Render() {
    if (sprite != nullptr) {
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
    const sf::Vector2f textureCenter = {0.5F * textureSize.x,
                                        0.5F * textureSize.y};
    sprite->setOrigin(textureCenter);
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