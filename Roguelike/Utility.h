#pragma once
#include "Vector.h"

namespace Roguelike {
template <typename T>
bool InRect(MaxrEngine::Vector2D<T> rectTopLeft,
            MaxrEngine::Vector2D<T> rectSize,
            MaxrEngine::Vector2D<T> position) {
    MaxrEngine::Vector2D<T> bottomRight = rectTopLeft + rectSize;
    return (rectTopLeft.x <= position.x && position.x < bottomRight.x) &&
           (rectTopLeft.y <= position.y && position.y < bottomRight.y);
}

template <typename T>
bool InRange(T value, T minValue, T maxValue) {
    return minValue <= value && value <= maxValue;
}

template <typename T>
T Half(const T& value) {
    constexpr float half = 0.5F;
    return half * value;
}

template <typename T>
bool OnSegment(MaxrEngine::Vector2D<T> pointToCheck,
               MaxrEngine::Vector2D<T> firstSegmentPoint,
               MaxrEngine::Vector2D<T> secondSegmentPoint) {
    return (pointToCheck.x == firstSegmentPoint.x &&
            InRange(pointToCheck.y,
                    std::min(firstSegmentPoint.y, secondSegmentPoint.y),
                    std::max(firstSegmentPoint.y, secondSegmentPoint.y))) ||
           (pointToCheck.y == firstSegmentPoint.y &&
            InRange(pointToCheck.x,
                    std::min(firstSegmentPoint.x, secondSegmentPoint.x),
                    std::max(firstSegmentPoint.x, secondSegmentPoint.x)));
}
}  // namespace Roguelike
