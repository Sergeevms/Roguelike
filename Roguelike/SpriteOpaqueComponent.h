#pragma once
#include "SFML/Graphics/Sprite.hpp"

#include "GameObject.h"
#include "OpaqueComponent.h"

namespace Roguelike {
class SpriteOpaqueComponent : public OpaqueComponent {
   public:
    explicit SpriteOpaqueComponent(MaxrEngine::GameObject* gameObject);
    ~SpriteOpaqueComponent();

    void Update(float deltaTime) override;
    void Render() override;

   private:
    const sf::Sprite* sprite;
};
}  // namespace Roguelike
