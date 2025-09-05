#pragma once
#include <memory>
#include <utility>
#include <vector>

#include "Labyrinth.h"
#include "Vector.h"

namespace Roguelike {
class NavigationSystem {
   public:
    static std::shared_ptr<NavigationSystem> Instance();
    void SetUpMap(const Labyrinth& labyrinth);

    std::vector<MaxrEngine::Vector2Df> GetPath(
        const MaxrEngine::Vector2Df& begin, const MaxrEngine::Vector2Df& end);

   private:
    struct Node {
        MaxrEngine::Vector2Df coordinates;
        std::vector<Node*> visibleNodes;
    };
    std::vector<std::unique_ptr<Node>> nodes;
    std::vector<std::pair<Node*, Node*>> edges;
    NavigationSystem() = default;
};

}  // namespace Roguelike
