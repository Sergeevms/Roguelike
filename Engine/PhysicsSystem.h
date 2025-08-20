#pragma once
#include <map>
#include <vector>

#include "Collision.h"
#include "EngineAPI.h"
#include "IFixedUpdateSystem.h"
#include "Trigger.h"

namespace MaxrEngine {
class ColliderComponent;
class PhysicsSystem : public IFixedUpdateSystem {
   public:
    ENGINE_API static PhysicsSystem* Instance();

    void Update() override;

    ENGINE_API void Subscribe(ColliderComponent* collider);
    ENGINE_API void Unsubscribe(ColliderComponent* collider);

   private:
    PhysicsSystem() {};
    ~PhysicsSystem() {};

    PhysicsSystem(PhysicsSystem const&) = delete;
    PhysicsSystem& operator=(PhysicsSystem const&) = delete;

    static void ProcessCollision(Collision* collision);
    void ProcessTriggerEnter(Trigger* trigger);

    std::vector<ColliderComponent*> colliders;
    std::map<ColliderComponent*, ColliderComponent*> triggersEnteredPair;
};
}  // namespace MaxrEngine
