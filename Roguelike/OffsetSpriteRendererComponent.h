#pragma once
#include "GameObject.h"
#include "SpriteRendererComponent.h"
#include "Vector.h"
namespace Roguelike {
class OffsetSpriteRendererComponent
    : public MaxrEngine::SpriteRendererComponent {
   public:
    explicit OffsetSpriteRendererComponent(
        MaxrEngine::GameObject* gameObject,
        const MaxrEngine::Vector2Df& offset = MaxrEngine::Vector2Df(0.0F, 0.0F),
        const int layer = 0);

    void Render() override;
    void SetOffset(MaxrEngine::Vector2Df& newOffset);
    const MaxrEngine::Vector2Df& GetOffset() const;

   private:
    MaxrEngine::Vector2Df offset;
};
}  // namespace Roguelike
