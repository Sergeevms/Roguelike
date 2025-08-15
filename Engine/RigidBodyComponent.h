#pragma once
#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace MaxrEngine {
class RigidBodyComponent : public Component {
   public:
    explicit ENGINE_API RigidBodyComponent(GameObject* gameObject,
                                           const bool isKinematic = false);

    void Update(float deltaTime) override;

    ENGINE_API void SetLinearVelocity(Vector2Df newLinearVelocity);
    ENGINE_API void AddLinearVelocity(Vector2Df linearOffset);
    ENGINE_API Vector2Df GetLinearVelocity() const;

    ENGINE_API void SetAngleVelocity(float newAngleVelocity);
    ENGINE_API void AddAngleVelocity(float angleOffset);
    ENGINE_API float GetAngleVelocity() const;

    ENGINE_API void SetLinearDamping(float newLinearDamping);
    ENGINE_API float GetLinearDamping() const;

    ENGINE_API void SetAngleDamping(float newAngleDamping);
    ENGINE_API float GetAngleDamping() const;

    ENGINE_API void SetKinematic(bool newIsKinematic);
    ENGINE_API bool GetKinematic() const;

   private:
    TransformComponent* transform;

    Vector2Df linearVelocity = {0.0F, 0.0F};
    float angleVelocity = 0.0F;

    float linearDamping = 0.0F;
    float angleDamping = 0.0F;

    bool isKinematic = false;
};
}  // namespace MaxrEngine
