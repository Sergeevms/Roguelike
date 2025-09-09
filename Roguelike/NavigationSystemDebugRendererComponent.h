#pragma once
#include <memory>

#include "SFML/Graphics/RenderTexture.hpp"
#include "SFML/Graphics/Sprite.hpp"

#include "Component.h"
#include "IObserver.h"
#include "IRenderable.h"

namespace Roguelike {
class NavigationSystemDebugRendererComponent : public MaxrEngine::Component,
                                               public MaxrEngine::IRenderable,
                                               public MaxrEngine::IObserver {
   public:
    explicit NavigationSystemDebugRendererComponent(
        MaxrEngine::GameObject* gameObject, const int layer = 0);
    void Update(float deltaTime) override;
    void Render() override;
    void Notify(std::shared_ptr<MaxrEngine::IObservable> observable) override;

   private:
    sf::RenderTexture texture;
    sf::Sprite sprite;
};
}  // namespace Roguelike
