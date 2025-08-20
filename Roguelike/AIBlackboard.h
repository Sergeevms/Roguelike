#pragma once
#include <vector>

#include "AITypedBlackboardComponent.h"
#include "GameObject.h"
#include "Vector.h"

namespace Roguelike {
using AIBlackboard = MaxrEngine::AITypedBlackboardComponent<
    bool, float, MaxrEngine::Vector2Df, MaxrEngine::GameObject*,
    std::vector<MaxrEngine::GameObject*>*>;
}
