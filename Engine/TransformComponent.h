#pragma once
#include "Component.h"
#include "Matrix2D.h"
#include "Vector.h"

namespace MaxrEngine {
class GameObject;

class TransformComponent : public Component {
   public:
    explicit TransformComponent(GameObject* gameObject);

    void Update(float deltaTime) override;

    void MoveBy(const Vector2Df& offset);
    void MoveBy(float offsetX, float offsetY);
    void SetWorldPosition(const Vector2Df& position);
    void SetWorldPosition(float positionX, float positionY);
    void SetLocalPosition(const Vector2Df& position);
    void SetLocalPosition(float positionX, float positionY);

    void RotateBy(const float offset);
    void SetWorldRotation(float angle);
    void SetLocalRotation(float angle);

    void ScaleBy(const Vector2Df& offset);
    void ScaleBy(float offsetX, float offsetY);
    void SetWorldScale(const Vector2Df& scale);
    void SetWorldScale(float scaleX, float scaleY);
    void SetLocalScale(const Vector2Df& scale);
    void SetLocalScale(float scaleX, float scaleY);

    const Vector2Df& GetWorldPosition() const;
    const Vector2Df& GetLocalPosition() const;

    float GetWorldRotation() const;
    float GetLocalRotation() const;

    void SetParent(TransformComponent* newParent);
    TransformComponent* GetParent() const;

    Matrix2D GetWorldTransform() const;
    void Print() const;

    const Vector2Df& GetWorldScale() const;
    const Vector2Df& GetLocalScale() const;

   private:
    static const Vector2Df defaultScale;
    static const Vector2Df defaultPosition;
    TransformComponent* parent = nullptr;

    mutable Matrix2D localTransform;
    mutable bool isUpdated = false;

    mutable Vector2Df localPosition = defaultPosition;
    mutable float localRotation = 0.0F;
    mutable Vector2Df localScale = defaultScale;

    mutable Vector2Df position = defaultPosition;
    mutable float rotation = 0.0F;
    mutable Vector2Df scale = defaultScale;

    void SetWorldInfoFrom(const Matrix2D& transform) const;
    void SetLocalInfoFrom(const Matrix2D& transform) const;
    void UpdateLocalTransform() const;
    void UpdateLocalTransform(const Vector2Df& position, const float rotation,
                              const Vector2Df& scale) const;
    static Matrix2D CreateTransform(const Vector2Df& position,
                                    const float rotation,
                                    const Vector2Df& scale);
};
}  // namespace MaxrEngine
