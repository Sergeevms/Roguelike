#pragma once
#include <memory>

#include "Component.h"
#include "EngineAPI.h"
#include "InputComponent.h"
#include "SpriteRendererComponent.h"
namespace MaxrEngine {
/**
 * @brief Component that flip SpriteRenderComponent to input direction.
 */
class SpriteDirectionComponent : public Component {
   public:
    explicit ENGINE_API SpriteDirectionComponent(GameObject* gameObject);
    void Update(float deltaTime) override;
    void Render() override;

   private:
    std::weak_ptr<SpriteRendererComponent> rendererPointer;
    std::weak_ptr<InputComponent> inputPointer;
};
}  // namespace MaxrEngine
