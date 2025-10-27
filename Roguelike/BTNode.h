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
}  // namespace Roguelike
