#pragma once

namespace MaxrEngine {
class GameObject;

class Component {
   public:
    explicit Component(GameObject* gameObject);
    virtual ~Component();

    virtual void Update(float deltaTime) = 0;

    GameObject* GetGameObject();

   protected:
    GameObject* gameObject;
};
}  // namespace MaxrEngine
