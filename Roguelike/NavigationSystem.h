#pragma once
#include <memory>
#include <utility>
#include <vector>

#include "IObserver.h"
#include "Labyrinth.h"
#include "NavigationSystemDebugRendererComponent.h"
#include "Vector.h"

namespace Roguelike {
class NavigationSystem : public MaxrEngine::IObservable {
   public:
    friend class NavigationSystemDebugRendererComponent;
    static std::shared_ptr<NavigationSystem> Instance();
    void SetUpMap(const Labyrinth& labyrinth);

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
    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<std::pair<Node*, Node*>> borders;
    std::weak_ptr<const Labyrinth> labyrinth;
    bool IsNotCrossingBorders(const Node* first, const Node* second);
    NavigationSystem() = default;
};

}  // namespace Roguelike
