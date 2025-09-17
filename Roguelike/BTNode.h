#pragma once
#include <memory>
#include <string_view>
#include <vector>

#include "AIBlackboard.h"
#include "GameObject.h"

namespace Roguelike {
/**
 * @brief Base class for all Behavior Tree nodes.
 *
 * Provides the fundamental interface for behavior tree nodes with three
 * possible states: Success, Failure, and Running.
 */
class BTNode {
   public:
    /// @brief Possible states for a node after execution
    enum class Status {
        Success,  ///< The node completed successfully
        Failure,  ///< The node failed to complete
        Running   ///< The node is still executing (will continue next tick)
    };
    static constexpr std::string_view deltaTimeBBName = "BT_deltaTime";
    virtual ~BTNode() = default;
    /**
     * @brief Execute the node's behavior
     * @param object The game object this node is acting upon
     * @param blackboard The data storage for AI information
     * @return Status indicating the result of execution
     */
    virtual Status Execute(MaxrEngine::GameObject* object,
                           AIBlackboard* blackboard) = 0;
};
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

   protected:
    std::vector<std::unique_ptr<BTNode>> childs;  ///< Collection of child nodes
    int currentChild = 0;  ///< Index of the current child being executed
};
/**
 * @brief Base class for decorator nodes that modify behavior of a single child.
 *
 * Decorators can modify the result of their child node or add additional
 * conditions.
 */
class BTDecorator : public BTNode {
   public:
    /**
     * @brief Set the child node for this decorator
     * @param newChild The child node (transfers ownership)
     */
    void SetChild(std::unique_ptr<BTNode>&& newChild);

   private:
    std::unique_ptr<BTNode> child;  ///< The single child node
};
/**
 * @brief Sequence node that executes children in order until one fails or all
 * succeed.
 *
 * @details A sequence will execute each child in order. If any child fails, the
 * sequence fails. If a child returns Running, the sequence pauses and continues
 * with that child next tick. Only returns Success if all children succeed.
 */
class BTSequence : public BTComposite {
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
class BTSelector : public BTComposite {
   public:
    Status Execute(MaxrEngine::GameObject* object,
                   AIBlackboard* blackboard) override;
};
}  // namespace Roguelike
