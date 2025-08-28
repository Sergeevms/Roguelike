#pragma once
#include "SFML/Graphics/Sprite.hpp"

#include "GameObject.h"
#include "IRenderable.h"
#include "OpaqueComponent.h"

namespace Roguelike {
class SpriteOpaqueComponent : public OpaqueComponent,
                              public MaxrEngine::IRenderable {
   public:
    explicit SpriteOpaqueComponent(MaxrEngine::GameObject* gameObject,
                                   const int layer = 0);
    ~SpriteOpaqueComponent();

    void Update(float deltaTime) override;
    void Render() override;

   private:
    const sf::Sprite* sprite;
};
}  // namespace Roguelike
