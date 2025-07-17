#pragma once
#include "SFML/Graphics/Rect.hpp"

#include "Component.h"

namespace Roguelike {
class OpaqueComponent : public MaxrEngine::Component {
   public:
    friend class PerceptionSystem;

    explicit OpaqueComponent(MaxrEngine::GameObject* gameObject);
    ~OpaqueComponent();

    void Update(float deltaTime) override;
    void Render() override;

   protected:
    sf::FloatRect bounds;
};
}  // namespace Roguelike
