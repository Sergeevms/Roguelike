#pragma once
#include "GameObject.h"

namespace Roguelike {
class GameObjectContainer {
   public:
    GameObjectContainer();
    GameObjectContainer(std::string objectName);
    MaxrEngine::GameObject* GetGameObject();

   protected:
    MaxrEngine::GameObject* gameObject;
};
}  // namespace Roguelike
