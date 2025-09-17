#pragma once
#include <optional>
#include <vector>

#include "AITypedBlackboardComponent.h"
#include "GameObject.h"
#include "Vector.h"

namespace Roguelike {
using AIBlackboard = MaxrEngine::AITypedBlackboardComponent<
    bool, float, int, MaxrEngine::Vector2Df,
    std::optional<MaxrEngine::Vector2Df>,
    std::shared_ptr<std::vector<MaxrEngine::Vector2Df>>, std::optional<float>,
    MaxrEngine::GameObject *, std::vector<MaxrEngine::GameObject *> *>;
}
