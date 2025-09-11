#pragma once
#include <memory>

#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include "Component.h"
#include "IObserver.h"
#include "IRenderable.h"

namespace Roguelike {
/**
 * @class NavigationSystemDebugRendererComponent
 * @brief Renders debug visualization of navigation graph
 *
 * Observes NavigationSystem changes and renders nodes/edges using SFML.
 * Attach to GameObject for automatic rendering.
 */
class NavigationSystemDebugRendererComponent : public MaxrEngine::Component,
                                               public MaxrEngine::IRenderable,
                                               public MaxrEngine::IObserver {
   public:
    /**
     * @brief Constructor
     * @param gameObject Parent GameObject
     * @param layer Rendering layer (higher values draw on top)
     */
    explicit NavigationSystemDebugRendererComponent(
        MaxrEngine::GameObject* gameObject, const int layer = 0);
    void Update(float deltaTime) override;
    void Render() override;
    /**
     * @brief Handle NavigationSystem update events
     * @param observable Typically NavigationSystem instance
     */
    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;

   private:
    sf::RenderTexture texture;  // Render target for navigation graph
    sf::Sprite sprite;          // Final rendered sprite
};
}  // namespace Roguelike
