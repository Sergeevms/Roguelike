#pragma once
#include <memory>
#include <vector>

#include "AIBlackboard.h"
#include "BTNode.h"
#include "GameObject.h"
namespace Roguelike {
/**
 * @brief Base class for composite nodes that have multiple children.
 *
 * Composite nodes control the flow of execution through their children.
 * Manages the current child index to remember where execution stopped.
 */
class BTComposite : public BTNode {
   public:
    /**
     * @brief Add a child node to this composite
     * @param newChild The child node to add (transfers ownership)
     */
    void AddChild(std::unique_ptr<BTNode>&& newChild);
    BTNode* GetChild(const int childIndex) const;
    std::vector<BTNode*> GetNodes() const;

   protected:
    std::vector<std::unique_ptr<BTNode>>
        childNodes;  ///< Collection of child nodes
};
/**
 * @brief Base class for composite nodes that have multiple children.
 *
 * Composite nodes control the flow of execution through their children.
 * Manages the current child index to remember where execution stopped.
 */
class BTCompositeWithMemory : public BTComposite {
   protected:
    int currentChild = 0;  ///< Index of the current child being executed
};

/**
 * @brief Sequence node that executes children in order until one fails or all
 * succeed.
 *
 * @details A sequence will execute each child in order. If any child fails, the
 * sequence fails. Only returns Success if all children succeed.
 */
class BTSequence : public BTComposite {
   public:
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
/**
 * @brief Selector node that executes children until one succeeds or all fail,
 * remembers child returned running last time.
 *
 * @details A selector will execute each child in order until one succeeds. If
 * any child succeeds, the selector succeeds. If a child returns Running, the
 * selector pauses and continues with that child next tick. Only returns Failure
 * if all children fail.
 */
class BTSequenceWM : public BTCompositeWithMemory {
   public:
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
/**
 * @brief Selector node that executes children until one succeeds or all fail.
 *
 * @details A selector will execute each child in order until one succeeds. If
 * any child succeeds, the selector succeeds. Only returns Failure
 * if all children fail.
 */
class BTSelector : public BTComposite {
   public:
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
/**
 * @brief Selector node that executes children until one succeeds or all fail.
 *
 * @details A selector will execute each child in order until one succeeds. If
 * any child succeeds, the selector succeeds. If a child returns Running, the
 * selector pauses and continues with that child next tick. Only returns Failure
 * if all children fail.
 */
class BTSelectorWM : public BTCompositeWithMemory {
   public:
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
class BTTimeRestartingSequence : public BTSequenceWM {
   public:
    explicit BTTimeRestartingSequence(const float timeTillRestart = 0.0F);
    void SetUpRestartTime(const float newTimeTillRestart);
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;

   private:
    float timeTillRestart;
    float timer;
};
class BTParallel : public BTCompositeWithMemory {
   public:
    explicit BTParallel(const int nodesToSuccess = 1);
    void SetUpSuccessNodesCount(const int newNodesToSuccess);
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;

   private:
    int nodesToSuccess;
};
}  // namespace Roguelike