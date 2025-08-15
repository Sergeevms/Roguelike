#pragma once
#include "Component.h"
#include "EngineAPI.h"
#include "Matrix2D.h"
#include "Vector.h"

namespace MaxrEngine {
class GameObject;

class TransformComponent : public Component {
   public:
    explicit ENGINE_API TransformComponent(GameObject* gameObject);

    void Update(float deltaTime) override;

    ENGINE_API void MoveBy(const Vector2Df& offset);
    ENGINE_API void MoveBy(float offsetX, float offsetY);
    ENGINE_API void SetWorldPosition(const Vector2Df& position);
    ENGINE_API void SetWorldPosition(float positionX, float positionY);
    ENGINE_API void SetLocalPosition(const Vector2Df& position);
    ENGINE_API void SetLocalPosition(float positionX, float positionY);

    ENGINE_API void RotateBy(const float offset);
    ENGINE_API void SetWorldRotation(float angle);
    ENGINE_API void SetLocalRotation(float angle);

    ENGINE_API void ScaleBy(const Vector2Df& offset);
    ENGINE_API void ScaleBy(float offsetX, float offsetY);
    ENGINE_API void SetWorldScale(const Vector2Df& scale);
    ENGINE_API void SetWorldScale(float scaleX, float scaleY);
    ENGINE_API void SetLocalScale(const Vector2Df& scale);
    ENGINE_API void SetLocalScale(float scaleX, float scaleY);

    ENGINE_API const Vector2Df& GetWorldPosition() const;
    ENGINE_API const Vector2Df& GetLocalPosition() const;

    ENGINE_API float GetWorldRotation() const;
    ENGINE_API float GetLocalRotation() const;

    ENGINE_API void SetParent(TransformComponent* newParent);
    ENGINE_API TransformComponent* GetParent() const;

    ENGINE_API Matrix2D GetWorldTransform() const;
    ENGINE_API void Print() const;

    ENGINE_API const Vector2Df& GetWorldScale() const;
    ENGINE_API const Vector2Df& GetLocalScale() const;

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
