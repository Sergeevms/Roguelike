#pragma once
#include "Component.h"
#include "PerceptionComponent.h"

namespace Roguelike {
class PerceptionComponentDebugDraw : public MaxrEngine::Component {
   public:
    PerceptionComponentDebugDraw(MaxrEngine::GameObject* gameObject);

    virtual void Update(float deltaTime) override;
    virtual void Render() override;

    void setArcPointCount(unsigned newArcPointsCount);

   protected:
    std::weak_ptr<PerceptionComponent> perceptionComponent;
    unsigned arcLinesCount = 50;
};
}  // namespace Roguelike