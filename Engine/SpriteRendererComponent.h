#pragma once
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Component.h"
#include "EngineAPI.h"
#include "IRenderable.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace MaxrEngine {
class SpriteRendererComponent : public Component, public IRenderable {
   public:
    explicit ENGINE_API SpriteRendererComponent(GameObject* gameObject);
    ENGINE_API ~SpriteRendererComponent();

    void Update(float deltaTime) override;
    void Render() override;

    ENGINE_API const sf::Sprite* GetSprite() const;
    ENGINE_API void SetTexture(const sf::Texture& newTexture,
                               const bool newIsTextureRightDirected = true);
    ENGINE_API void SetPixelSize(const Vector2Di& size);
    ENGINE_API void SetPixelSize(int newWidth, int newHeight);
    ENGINE_API bool IsTextureRightDirected() const;
    ENGINE_API void SetColor(const sf::Color newColor);

    ENGINE_API void FlipX(bool flip);
    ENGINE_API void FlipY(bool flip);

   private:
    Vector2Df scale;
    sf::Sprite* sprite;
    TransformComponent* transform;

    bool isFlipX = false;
    bool isFlipY = false;
    /** Is setted texture directed to rigth*/
    bool isTextureRightDirected = true;
};
}  // namespace MaxrEngine
