#pragma once
namespace MaxrEngine {
class ColliderComponent;
struct Trigger {
   public:
    Trigger(ColliderComponent* first, ColliderComponent* second)
        : first(first), second(second) {};
    ColliderComponent* first;
    ColliderComponent* second;
};
}  // namespace MaxrEngine
