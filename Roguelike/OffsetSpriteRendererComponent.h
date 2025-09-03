#pragma once
#include "SFML/Graphics/Texture.hpp"

#include "GameObject.h"
#include "SpriteRendererComponent.h"
#include "Vector.h"
namespace Roguelike {
/**
 * @brief Extended sprite renderer with offset capabilities
 * @details Specialized sprite renderer that supports texture offsetting
 * and coefficient-based scaling for proper sprite alignment
 */
class OffsetSpriteRendererComponent
    : public MaxrEngine::SpriteRendererComponent {
   public:
    using Vector2Df = MaxrEngine::Vector2Df;
    using Vector2Di = MaxrEngine::Vector2Di;

    /**
     * @brief Parameters for offset sprite configuration
     */
    struct Parameters {
        Vector2Di originalSpriteTextureSize;  ///< Original texture dimensions
        Vector2Di
            originalImageSize;  ///< Actual image dimensions within texture
        Vector2Di originalCenterOffset;  ///< Offset from texture center to
                                         ///< image center
    };

    /**
     * @brief Constructs an OffsetSpriteRendererComponent
     * @param gameObject Parent GameObject
     * @param layer Render layer for depth sorting
     */
    explicit OffsetSpriteRendererComponent(MaxrEngine::GameObject* gameObject,
                                           const int layer = 0);
    /**
     * @brief Sets texture with offset parameters
     * @param newTexture Texture to apply
     * @param parameters Offset configuration parameters
     * @param newIsTextureRightDirected Texture direction flag
     */
    void SetTexture(const sf::Texture& newTexture, const Parameters& parameters,
                    const bool newIsTextureRightDirected = true);
    void Render() override;
    /**
     * @brief Configures offset parameters
     * @param parameters Offset configuration parameters
     */
    void SetOffsetParameters(const Parameters& parameters);

    void FlipX(bool flip) override;
    void FlipY(bool flip) override;

   private:
    Vector2Df offset = {0.0F, 0.0F};  ///< Current rendering center offset
    Vector2Df coefficient = {
        1.0F, 1.0F};  ///< Additional scaling coefficient from actual image
                      ///< dimensions to original texture texture size
};
}  // namespace Roguelike
