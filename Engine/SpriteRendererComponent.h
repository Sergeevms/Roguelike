#pragma once
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Component.h"
#include "IRenderable.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace MaxrEngine {
class SpriteRendererComponent : public Component, public IRenderable {
   public:
    explicit SpriteRendererComponent(GameObject* gameObject);
    ~SpriteRendererComponent();

    void Update(float deltaTime) override;
    void Render() override;

    const sf::Sprite* GetSprite() const;
    void SetTexture(const sf::Texture& newTexture,
                    const bool newIsTextureRightDirected = true);
    void SetPixelSize(const Vector2Di& size);
    void SetPixelSize(int newWidth, int newHeight);
    bool IsTextureRightDirected() const;
    void SetColor(const sf::Color newColor);

    void FlipX(bool flip);
    void FlipY(bool flip);

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
