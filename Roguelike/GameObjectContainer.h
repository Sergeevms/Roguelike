#pragma once
#include <string>

#include "GameObject.h"

namespace Roguelike {
class GameObjectContainer {
   public:
    GameObjectContainer();
    explicit GameObjectContainer(std::string objectName);
    MaxrEngine::GameObject* GetGameObject();

   protected:
    MaxrEngine::GameObject* gameObject;
};
}  // namespace Roguelike
