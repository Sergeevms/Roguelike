#include "pch.h"

#include "TransformComponent.h"

#include <numbers>

namespace MaxrEngine {
constexpr float PI = std::numbers::pi_v<float>;

TransformComponent::TransformComponent(GameObject* gameObject)
    : Component(gameObject) {}

void TransformComponent::Update(float deltaTime) {}

void TransformComponent::Render() {}

void TransformComponent::MoveBy(const Vector2Df& offset) {
    localPosition += offset;
    isUpdated = false;
}

void TransformComponent::MoveBy(float offsetX, float offsetY) {
    MoveBy({offsetX, offsetY});
}

void TransformComponent::SetWorldPosition(const Vector2Df& position) {
    if (parent == nullptr) {
        localPosition = position;
    } else {
        Matrix2D newWorldTransform =
            CreateTransform(position, GetWorldRotation(), GetWorldScale());
        localTransform =
            parent->GetWorldTransform().GetInversed() * newWorldTransform;

        SetLocalInfoFrom(localTransform);
    }

    isUpdated = false;
}

void TransformComponent::SetWorldPosition(float positionX, float positionY) {
    SetWorldPosition({positionX, positionY});
}

void TransformComponent::SetLocalPosition(const Vector2Df& position) {
    localPosition = position;
    isUpdated = false;
}

void TransformComponent::SetLocalPosition(float positionX, float positionY) {
    SetLocalPosition({positionX, positionY});
}

void TransformComponent::RotateBy(const float offset) {
    localRotation += offset;
    while (localRotation >= 360.f) {
        localRotation -= 360.f;
    }
    while (localRotation < 0.f) {
        localRotation += 360.f;
    }
    isUpdated = false;
}

void TransformComponent::SetWorldRotation(float angle) {
    if (parent == nullptr) {
        localRotation = angle;
    } else {
        Matrix2D newWorldTransform =
            CreateTransform(GetWorldPosition(), angle, GetWorldScale());
        localTransform =
            parent->GetWorldTransform().GetInversed() * newWorldTransform;

        SetLocalInfoFrom(localTransform);
    }
    isUpdated = false;
}

void TransformComponent::SetLocalRotation(float angle) {
    localRotation = angle;
    while (localRotation >= 360.f) {
        localRotation -= 360.f;
    }
    while (localRotation < 0.f) {
        localRotation += 360.f;
    }
    isUpdated = false;
}

void TransformComponent::ScaleBy(const Vector2Df& offset) {
    localScale *= offset;
    isUpdated = false;
}

void TransformComponent::ScaleBy(float offsetX, float offsetY) {
    ScaleBy({offsetX, offsetY});
}

void TransformComponent::SetWorldScale(const Vector2Df& newScale) {
    if (parent == nullptr) {
        localScale = newScale;
    } else {
        Matrix2D newWorldTransform =
            CreateTransform(GetWorldPosition(), GetWorldRotation(), newScale);
        localTransform =
            parent->GetWorldTransform().GetInversed() * newWorldTransform;

        SetLocalInfoFrom(localTransform);
    }

    isUpdated = false;
}

void TransformComponent::SetWorldScale(float scaleX, float scaleY) {
    SetWorldScale({scaleX, scaleY});
}

void TransformComponent::SetLocalScale(const Vector2Df& scale) {
    localScale = scale;
    isUpdated = false;
}

void TransformComponent::SetLocalScale(float scaleX, float scaleY) {
    SetLocalScale({scaleX, scaleY});
}

const Vector2Df& TransformComponent::GetWorldPosition() const {
    UpdateLocalTransform();
    if (parent == nullptr) {
        return GetLocalPosition();
    }

    SetWorldInfoFrom(parent->GetWorldTransform() * localTransform);
    return position;
}

const Vector2Df& TransformComponent::GetLocalPosition() const {
    UpdateLocalTransform();
    return localPosition;
}

const float TransformComponent::GetWorldRotation() const {
    UpdateLocalTransform();
    if (parent == nullptr) {
        return GetLocalRotation();
    }

    SetWorldInfoFrom(parent->GetWorldTransform() * localTransform);
    return rotation;
}

const float TransformComponent::GetLocalRotation() const {
    UpdateLocalTransform();
    return localRotation;
}

void TransformComponent::SetParent(TransformComponent* newParent) {
    if (parent == nullptr && newParent != nullptr) {
        newParent->gameObject->AddChild(gameObject);
        localTransform =
            newParent->GetWorldTransform().GetInversed() * localTransform;
    } else if (parent != nullptr && newParent == nullptr) {
        parent->gameObject->RemoveChild(gameObject);
        localTransform = parent->GetWorldTransform() * localTransform;
    } else if (parent != nullptr && newParent != nullptr) {
        parent->gameObject->RemoveChild(gameObject);
        newParent->gameObject->AddChild(gameObject);
        localTransform = newParent->GetWorldTransform().GetInversed() *
                         (parent->GetWorldTransform() * localTransform);
    }

    SetLocalInfoFrom(localTransform);

    parent = newParent;
    isUpdated = false;
}

TransformComponent* TransformComponent::GetParent() const { return parent; }

const Matrix2D TransformComponent::GetWorldTransform() const {
    UpdateLocalTransform();

    if (parent == nullptr) {
        return localTransform;
    }

    return parent->GetWorldTransform() * localTransform;
}

void TransformComponent::Print() const {
    std::cout << "Transform name : " << gameObject->GetName() << std::endl;

    std::cout << "Position" << std::endl;
    std::cout << "  World: (" << GetWorldPosition().x << ", "
              << GetWorldPosition().y << ")" << std::endl;
    std::cout << "  Local: (" << GetLocalPosition().x << ", "
              << GetLocalPosition().y << ")" << std::endl;

    std::cout << "Rotation" << std::endl;
    std::cout << "  World: " << GetWorldRotation() << std::endl;
    std::cout << "  Local: " << GetLocalRotation() << std::endl;

    std::cout << "Scale" << std::endl;
    std::cout << "  World: (" << GetWorldScale().x << ", " << GetWorldScale().y
              << ")" << std::endl;
    std::cout << "  Local: (" << GetLocalScale().x << ", " << GetLocalScale().y
              << ")" << std::endl;
}

const Vector2Df& TransformComponent::GetWorldScale() const {
    UpdateLocalTransform();
    if (parent == nullptr) {
        return GetLocalScale();
    }

    SetWorldInfoFrom(parent->GetWorldTransform() * localTransform);
    return scale;
}

const Vector2Df& TransformComponent::GetLocalScale() const {
    UpdateLocalTransform();
    return localScale;
}

void TransformComponent::SetWorldInfoFrom(const Matrix2D& transform) const {
    auto& transformMatrix = transform.GetMatrix();

    position.x = transformMatrix[0][2];
    position.y = transformMatrix[1][2];

    scale.x = std::sqrt(transformMatrix[0][0] * transformMatrix[0][0] +
                        transformMatrix[1][0] * transformMatrix[1][0]);
    scale.y = std::sqrt(transformMatrix[0][1] * transformMatrix[0][1] +
                        transformMatrix[1][1] * transformMatrix[1][1]);

    rotation =
        std::atan2(transformMatrix[0][1], transformMatrix[0][0]) * 180 / PI;
}

void TransformComponent::SetLocalInfoFrom(const Matrix2D& transform) const {
    auto& transformMatrix = transform.GetMatrix();

    localPosition.x = transformMatrix[0][2];
    localPosition.y = transformMatrix[1][2];

    localScale.x = std::sqrt(transformMatrix[0][0] * transformMatrix[0][0] +
                             transformMatrix[1][0] * transformMatrix[1][0]);
    localScale.y = std::sqrt(transformMatrix[0][1] * transformMatrix[0][1] +
                             transformMatrix[1][1] * transformMatrix[1][1]);

    localRotation =
        std::atan2(transformMatrix[0][1], transformMatrix[0][0]) * 180 / PI;
}

void TransformComponent::UpdateLocalTransform() const {
    if (!isUpdated) {
        localTransform =
            CreateTransform(localPosition, localRotation, localScale);
        isUpdated = true;
    }
}

void TransformComponent::UpdateLocalTransform(const Vector2Df& position,
                                              float rotation,
                                              const Vector2Df& scale) const {
    if (!isUpdated) {
        localTransform = CreateTransform(position, rotation, scale);
        isUpdated = true;
    }
}

Matrix2D TransformComponent::CreateTransform(const Vector2Df& position,
                                             float rotation,
                                             const Vector2Df& scale) const {
    return Matrix2D(position, rotation, scale);
}
}  // namespace MaxrEngine