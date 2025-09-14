#pragma once
#include <array>
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
    // Private constructor for singleton pattern
    NavigationSystem() = default;
    // Forward declarations
    struct Node;
    /**
     * @brief Create edges between visible nodes in the navigation graph
     */
    void CreateEdges();
    /**
     * @brief Check if line between two nodes doesn't cross any obstacle borders
     * @param firstNode First node to check
     * @param secondNode Second node to check
     * @return True if line is clear of obstacles, false if intersects any
     * borders
     */
    bool IsNotCrossingBorders(const Node* first, const Node* second);
    /**
     * @brief Get cells that need to be processed for navigation mesh generation
     * @return Vector of unwalkable cells that have at least one walkable
     * neighbor
     */
    std::vector<MaxrEngine::Vector2Di> GetCellsToProcess() const;
    /**
     * @brief Selects walkable area and create nodes and borders in it
     * @param[in,out] untouchedCells - unwalkable cells needed to be touched to
     * finish creating navigation graph
     */
    void ProcessArea(std::vector<MaxrEngine::Vector2Di>& untouchedCells);
    /**
     * @brief Represents a connection between two nodes in the navigation graph
     */
    struct Edge {
        Node* node = nullptr;   // Connected node
        float distance = 0.0F;  // Distance to connected node
    };
    /**
     * @brief Represents a node in the navigation graph
     */
    struct Node {
        MaxrEngine::Vector2Df coordinates;  // World coordinates of the node
        std::vector<Edge> edges;            // Connections to other nodes
    };
    std::vector<std::unique_ptr<Node>> nodes;      // Navigation graph nodes
    std::vector<std::pair<Node*, Node*>> borders;  // Obstacle boundary edges
    std::weak_ptr<const Labyrinth>
        labyrinthPtr;  // Weak pointer to labyrinth map data
    /**
     * @brief Represents cardinal directions with helper functions for
     * navigation
     */
    struct Direction {
        static constexpr int directionsCount = 4;   // Number of directions
        enum class Name { Left, Up, Right, Down };  // Direction names

        Direction() = default;
        explicit Direction(const Name direction);
        explicit Direction(const int direction);

        /**
         * @brief Convert direction to integer representation
         * @return Integer value of direction (0-3)
         */
        int ToInt() const;
        /**
         * @brief Convert direction name to integer representation
         * @param direction Direction name to convert
         * @return Integer value of direction (0-3)
         */
        static int ToInt(Name direction);

        // Direction manipulation methods
        void TurnLeft();
        static Direction TurnLeft(const Direction direction);
        static Direction TurnLeft(const Name direction);
        static Direction TurnLeft(const int direction);

        void TurnRight();
        static Direction TurnRight(const Direction direction);
        static Direction TurnRight(const Name direction);
        static Direction TurnRight(const int direction);

        // Direction vectors for each direction
        static const std::array<MaxrEngine::Vector2Di, directionsCount>
            directionVector;
        /**
         * @brief Get direction vector for current direction
         * @return Vector representing the direction
         */
        const MaxrEngine::Vector2Di& DirectionVector() const;
        /**
         * @brief Get direction vector for specified direction name
         * @param direction Direction name
         * @return Vector representing the direction
         */
        static const MaxrEngine::Vector2Di& DirectionVector(Name direction);
        /**
         * @brief Get direction vector for specified direction integer
         * @param direction Direction integer
         * @return Vector representing the direction
         */
        static const MaxrEngine::Vector2Di& DirectionVector(
            const int direction);
        /**
         * @brief Set offset values for placing Node in corner of walkable cell
         * @param offset Distance offset for corner placement
         */
        static void SetOffset(const float offset);
        // Offset used to place Node on left turns in algorithm
        static std::array<MaxrEngine::Vector2Df, directionsCount>
            leftTurnOffset;
        /**
         * @brief Get left turn offset for current direction
         * @return Offset vector for left turns
         */
        const MaxrEngine::Vector2Df& LeftTurnOffset() const;
        /**
         * @brief Get left turn offset for specified direction name
         * @param direction Direction name
         * @return Offset vector for left turns
         */
        static const MaxrEngine::Vector2Df& LeftTurnOffset(
            const Name direction);

        /**
         * @brief Get left turn offset for specified direction integer
         * @param direction Direction integer
         * @return Offset vector for left turns
         */
        static const MaxrEngine::Vector2Df& LeftTurnOffset(const int direction);

        // Offset used to place Node on right turns in algorithm
        static std::array<MaxrEngine::Vector2Df, directionsCount>
            rightTurnOffset;
        /**
         * @brief Get right turn offset for current direction
         * @return Offset vector for right turns
         */
        const MaxrEngine::Vector2Df& RightTurnOffset() const;
        /**
         * @brief Get right turn offset for specified direction name
         * @param direction Direction name
         * @return Offset vector for right turns
         */
        static const MaxrEngine::Vector2Df& RightTurnOffset(
            const Name direction);
        /**
         * @brief Get right turn offset for specified direction integer
         * @param direction Direction integer (0-3)
         * @return Offset vector for right turns
         */
        static const MaxrEngine::Vector2Df& RightTurnOffset(
            const int direction);

        auto operator<=>(const Direction&) const = default;

        Name value = Name::Left;
    };
};
}  // namespace Roguelike
