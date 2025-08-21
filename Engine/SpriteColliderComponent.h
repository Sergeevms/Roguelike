#pragma once
#include "SFML/Graphics/Sprite.hpp"

#include "ColliderComponent.h"
#include "GameObject.h"
#include "IRenderable.h"

namespace MaxrEngine {
class SpriteColliderComponent : public ColliderComponent, public IRenderable {
   public:
    explicit SpriteColliderComponent(GameObject* gameObject,
                                     int renderLayer = 0);
    ~SpriteColliderComponent();

    void Update(float deltaTime) override;
    void Render() override;

   private:
    const sf::Sprite* sprite;
};
}  // namespace MaxrEngine
