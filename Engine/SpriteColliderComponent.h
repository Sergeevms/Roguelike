#pragma once
#include "ColliderComponent.h"
#include "EngineAPI.h"

namespace MaxrEngine {
class SpriteColliderComponent : public ColliderComponent {
   public:
    ENGINE_API SpriteColliderComponent(GameObject* gameObject);
    ~SpriteColliderComponent();

    void Update(float deltaTime) override;
    void Render() override;

   private:
    const sf::Sprite* sprite;
};
}  // namespace MaxrEngine
