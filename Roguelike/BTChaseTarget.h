#pragma once
#include <memory>

#include "AIBlackboard.h"
#include "BTComposite.h"
#include "BTNode.h"
#include "DefaultActorsSettings.h"
#include "GameObject.h"
namespace Roguelike {
class BTChaseTarget : public BTSequence {
   public:
    static std::unique_ptr<BTChaseTarget> Create();

   private:
    BTChaseTarget() = default;
};
class BTIsTargetClose : public BTNode {
   public:
    static constexpr float closeDistance =
        0.7 * DefaultSettings::defaultActorSpriteSizeF;
    Status Execute(MaxrEngine::GameObject* object, AIBlackboard* blackboard);
};
class BTSetUpPathToTarget : public BTNode {
   public:
    Status Execute(MaxrEngine::GameObject* object, AIBlackboard* blackboard);
};
}  // namespace Roguelike
