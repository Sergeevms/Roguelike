#pragma once
#include <memory>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "Component.h"
#include "GameObject.h"
namespace Roguelike {
class AIControlComponent : public MaxrEngine::Component {
   public:
    explicit AIControlComponent(MaxrEngine::GameObject* gameObject,
                                std::unique_ptr<BTNode>&& bTRoot = nullptr);

    void Update(float deltaTime) override;

    void SetBTRoot(std::unique_ptr<BTNode>&& newBTRoot);

   private:
    std::unique_ptr<BTNode> root;
    AIBlackboard* blackboard;
};
}  // namespace Roguelike
