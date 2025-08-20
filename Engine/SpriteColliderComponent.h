#pragma once
#include "SFML/Graphics/Sprite.hpp"

#include "ColliderComponent.h"
#include "EngineAPI.h"
#include "GameObject.h"

namespace MaxrEngine {
class SpriteColliderComponent : public ColliderComponent {
   public:
    explicit ENGINE_API SpriteColliderComponent(GameObject* gameObject);
    ~SpriteColliderComponent();

    void Update(float deltaTime) override;
    void Render() override;

   private:
    const sf::Sprite* sprite;
};
}  // namespace MaxrEngine
