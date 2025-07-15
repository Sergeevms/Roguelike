#include "GameObjectContainer.h"

#include "GameWorld.h"

namespace Roguelike {
GameObjectContainer::GameObjectContainer() {
    gameObject = MaxrEngine::GameWorld::Instance()->CreateGameObject();
}

GameObjectContainer::GameObjectContainer(std::string objectName) {
    gameObject =
        MaxrEngine::GameWorld::Instance()->CreateGameObject(objectName);
}

MaxrEngine::GameObject* GameObjectContainer::GetGameObject() {
    return gameObject;
}
}  // namespace Roguelike