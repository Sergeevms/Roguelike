#pragma once
#include <memory>

#include "Component.h"
#include "InputComponent.h"
#include "SpriteRendererComponent.h"
namespace MaxrEngine {
/**
 * @brief Component that flip SpriteRenderComponent to input direction.
 */
class SpriteDirectionComponent : public Component {
   public:
    explicit SpriteDirectionComponent(GameObject* gameObject);
    void Update(float deltaTime) override;

   private:
    std::weak_ptr<SpriteRendererComponent> rendererPointer;
    std::weak_ptr<InputComponent> inputPointer;
};
}  // namespace MaxrEngine
