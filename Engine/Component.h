#pragma once
#include "EngineAPI.h"
namespace MaxrEngine {
class GameObject;

class ENGINE_API Component {
   public:
    explicit Component(GameObject* gameObject);
    virtual ~Component();

    virtual void Update(float deltaTime) = 0;

    GameObject* GetGameObject();

   protected:
    GameObject* gameObject;
};
}  // namespace MaxrEngine
