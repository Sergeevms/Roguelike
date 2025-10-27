#pragma once
#include <memory>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "GameObject.h"

namespace Roguelike {
/**
 * @brief Base class for decorator nodes that modify behavior of a single child.
 *
 * Decorators can modify the result of their child node or add additional
 * conditions.
 */
class BTDecorator : public BTNode {
   public:
    BTDecorator() = default;
    explicit BTDecorator(std::unique_ptr<BTNode>&& child);
    /**
     * @brief Set the child node for this decorator
     * @param newChild The child node (transfers ownership)
     */
    void SetChild(std::unique_ptr<BTNode>&& newChild);
    BTNode* GetChild() const;

   protected:
    std::unique_ptr<BTNode> child;  ///< The single child node
};
class BTRepeatUntilFailure : public BTDecorator {
   public:
    BTRepeatUntilFailure() = default;
    explicit BTRepeatUntilFailure(std::unique_ptr<BTNode>&& child);
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
class BTInverter : public BTDecorator {
   public:
    BTInverter() = default;
    explicit BTInverter(std::unique_ptr<BTNode>&& child);
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
}  // namespace Roguelike
