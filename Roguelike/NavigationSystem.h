#pragma once
#include <memory>
#include <utility>
#include <vector>

#include "IObserver.h"
#include "Labyrinth.h"
#include "Vector.h"

namespace Roguelike {
/**
 * @brief Singleton class handling pathfinding and navigation using A*
 * algorithm.
 *
 * @details Maintains a navigation graph of nodes and edges. Supports
 * pathfinding between points while avoiding obstacles. Implements observable
 * pattern for debug rendering.
 */
class NavigationSystem : public MaxrEngine::IObservable {
   public:
    friend class NavigationSystemDebugRendererComponent;
    /**
     * @brief Get singleton instance
     * @return Shared pointer to NavigationSystem instance
     */
    static std::shared_ptr<NavigationSystem> Instance();
    /**
     * @brief Initialize navigation graph from labyrinth map
     * @param newLabyrinth Shared pointer to const Labyrinth map data
     */
    void SetUpMap(std::shared_ptr<const Labyrinth> newLabyrinth);
    /**
     * @brief Calculate path between two points using A* algorithm
     * @param begin Start position in world coordinates
     * @param end Target position in world coordinates
     * @return Vector of waypoints from start to end. Empty if no path exists.
     */
    std::vector<MaxrEngine::Vector2Df> GetPath(
        const MaxrEngine::Vector2Df& begin, const MaxrEngine::Vector2Df& end);

   private:
    struct Node;
    struct Edge {
        Node* node = nullptr;
        float distance = 0.0F;
    };
    struct Node {
        MaxrEngine::Vector2Df coordinates;
        std::vector<Edge> edges;
    };
    std::vector<std::unique_ptr<Node>> nodes;      // Navigation graph nodes
    std::vector<std::pair<Node*, Node*>> borders;  // Obstacle boundary edges
    std::weak_ptr<const Labyrinth>
        labyrinthPtr;  // Pointer to Labyrinth used for map data
    /**
     * @brief Check if line between two nodes doesn't cross any obstacle borders
     * @param first First node
     * @param second Second node
     * @return True if line is clear, false if intersects obstacles
     */
    bool IsNotCrossingBorders(const Node* first, const Node* second);

    void AddEdges();

    NavigationSystem() = default;
};

}  // namespace Roguelike
