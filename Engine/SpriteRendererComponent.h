#pragma once
#include <SFML/Graphics.hpp>

#include "Component.h"
#include "EngineAPI.h"
#include "TransformComponent.h"

namespace MaxrEngine {
class SpriteRendererComponent : public Component {
   public:
    ENGINE_API SpriteRendererComponent(GameObject* gameObject);
    ENGINE_API ~SpriteRendererComponent();

    virtual void Update(float deltaTime) override;
    virtual void Render() override;

    ENGINE_API const sf::Sprite* GetSprite() const;
    ENGINE_API void SetTexture(const sf::Texture& newTexture);
    ENGINE_API void SetPixelSize(int newWidth, int newHeight);

    ENGINE_API void FlipX(bool flip);
    ENGINE_API void FlipY(bool flip);

   private:
    Vector2Df scale;
    sf::Sprite* sprite;
    TransformComponent* transform;

    bool isFlipX = false;
    bool isFlipY = false;
};
}  // namespace MaxrEngine
