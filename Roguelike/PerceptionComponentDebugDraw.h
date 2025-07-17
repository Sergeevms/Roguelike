#pragma once
#include <memory>

#include "Component.h"
#include "PerceptionComponent.h"

namespace Roguelike {
class PerceptionComponentDebugDraw : public MaxrEngine::Component {
   public:
    static constexpr int defaultArcLineCount = 50;
    explicit PerceptionComponentDebugDraw(
        MaxrEngine::GameObject* gameObject,
        const int arcLinesCount = defaultArcLineCount);

    void Update(float deltaTime) override;
    void Render() override;

    void setArcPointCount(const int newArcPointsCount);
    int getArcPointCount() const;

   protected:
    std::weak_ptr<PerceptionComponent> perceptionComponent;
    int arcLinesCount;
};
}  // namespace Roguelike