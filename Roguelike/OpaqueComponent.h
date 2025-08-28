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

   protected:
    sf::FloatRect bounds;
};
}  // namespace Roguelike
