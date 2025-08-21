#pragma once
#include <map>
#include <vector>

#include "Collision.h"
#include "IFixedUpdateSystem.h"
#include "Trigger.h"

namespace MaxrEngine {
class ColliderComponent;
class PhysicsSystem : public IFixedUpdateSystem {
   public:
    static PhysicsSystem* Instance();

    void Update() override;

    void Subscribe(ColliderComponent* collider);
    void Unsubscribe(ColliderComponent* collider);

   private:
    PhysicsSystem() {};
    ~PhysicsSystem() {};

    PhysicsSystem(PhysicsSystem const&) = delete;
    PhysicsSystem& operator=(PhysicsSystem const&) = delete;

    static void ProcessCollision(Collision* collision);
    void ProcessTriggering(Trigger* trigger);

    std::vector<ColliderComponent*> colliders;
    std::map<ColliderComponent*, ColliderComponent*> triggersEnteredPair;
};
}  // namespace MaxrEngine
