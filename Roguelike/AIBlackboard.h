#pragma once
#include "AITypedBlackboardComponent.h"
#include "Vector.h"
namespace Roguelike {
using AIBlackboard = MaxrEngine::AITypedBlackboardComponent<
    bool, float, MaxrEngine::Vector2Df, MaxrEngine::GameObject*,
    std::vector<MaxrEngine::GameObject*>*>;
}
