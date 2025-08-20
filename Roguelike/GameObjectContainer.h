#pragma once
#include <string>

#include "GameObject.h"

namespace Roguelike {
class GameObjectContainer {
   public:
    GameObjectContainer();
    virtual ~GameObjectContainer() = default;
    explicit GameObjectContainer(std::string objectName);
    MaxrEngine::GameObject* GetGameObject();

   protected:
    MaxrEngine::GameObject* gameObject;
};
}  // namespace Roguelike
