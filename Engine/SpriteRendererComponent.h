#pragma once
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Component.h"
#include "IRenderable.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace MaxrEngine {
/**
 * @brief Renders a sprite for a GameObject with various transformation
 * capabilities
 * @details Handles texture management, scaling, flipping, and color modulation
 * for sprites.
 */
class SpriteRendererComponent : public Component, public IRenderable {
   public:
    /**
     * @brief Constructs a SpriteRendererComponent
     * @param gameObject Parent GameObject that owns this component
     * @param layer Render layer for depth sorting (higher values render on top)
     */
    explicit SpriteRendererComponent(GameObject* gameObject,
                                     const int layer = 0);
    ~SpriteRendererComponent();

    void Update(float deltaTime) override;
    void Render() override;

    /**
     * @brief Gets the underlying SFML sprite
     * @return Const pointer to the internal sf::Sprite object
     */
    const sf::Sprite* GetSprite() const;
    /**
     * @brief Sets the texture for the sprite
     * @param newTexture Texture to apply to the sprite
     * @param newIsTextureRightDirected Direction flag for texture orientation
     */
    void SetTexture(const sf::Texture& newTexture,
                    const bool newIsTextureRightDirected = true);
    /**
     * @brief Sets the pixel dimensions of the rendered sprite
     * @param size Vector representing width and height in pixels
     */
    void SetPixelSize(const Vector2Di& size);
    /**
     * @brief Sets the pixel dimensions of the rendered sprite
     * @param newWidth Width in pixels
     * @param newHeight Height in pixels
     */
    void SetPixelSize(int newWidth, int newHeight);
    /**
     * @brief Get info if the texture is right-directed
     * @return True if texture faces right, false otherwise
     */
    bool IsTextureRightDirected() const;
    /**
     * @brief Sets color modulation for the sprite
     * @param newColor SFML Color to apply to the sprite
     */
    void SetColor(const sf::Color newColor);
    /**
     * @brief Flips the sprite horizontally
     * @param flip True to flip horizontally, false to reset
     */
    virtual void FlipX(bool flip);
    /**
     * @brief Flips the sprite vertically
     * @param flip True to flip vertically, false to reset
     */
    virtual void FlipY(bool flip);

   protected:
    Vector2Df scale;     ///< Scale factors for sprite rendering
    sf::Sprite* sprite;  ///< Pointer to the SFML sprite object
    TransformComponent*
        transform;  ///< Reference to parent's transform component

    bool isFlipX = false;  ///< Horizontal flip state
    bool isFlipY = false;  ///< Vertical flip state

    bool isTextureRightDirected =
        true;  ///< Indicates if the set texture is directed to the right
};
}  // namespace MaxrEngine
