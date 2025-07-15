#pragma once

#include "Component.h"
#include "TransformComponent.h"

namespace MaxrEngine {
class RigidBodyComponent : public Component {
   public:
    ENGINE_API RigidBodyComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

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

    Vector2Df linearVelocity = {0.f, 0.f};
    float angleVelocity = 0.f;

    float linearDamping = 0.f;
    float angleDamping = 0.f;

    bool isKinematic = false;
};
}  // namespace MaxrEngine
