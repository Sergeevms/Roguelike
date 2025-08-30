#pragma once
#include "Component.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Vector.h"

namespace MaxrEngine {
class RigidBodyComponent : public Component {
   public:
    explicit RigidBodyComponent(GameObject* gameObject,
                                const bool isKinematic = false);

    void Update(float deltaTime) override;

    void SetLinearVelocity(Vector2Df newLinearVelocity);
    void AddLinearVelocity(Vector2Df linearOffset);
    Vector2Df GetLinearVelocity() const;

    void SetAngleVelocity(float newAngleVelocity);
    void AddAngleVelocity(float angleOffset);
    float GetAngleVelocity() const;

    void SetLinearDamping(float newLinearDamping);
    float GetLinearDamping() const;

    void SetAngleDamping(float newAngleDamping);
    float GetAngleDamping() const;

    void SetKinematic(bool newIsKinematic);
    bool GetKinematic() const;

   private:
    TransformComponent* transform;

    Vector2Df linearVelocity = {0.0F, 0.0F};
    float angleVelocity = 0.0F;

    float linearDamping = 0.0F;
    float angleDamping = 0.0F;

    bool isKinematic = false;
};
}  // namespace MaxrEngine
