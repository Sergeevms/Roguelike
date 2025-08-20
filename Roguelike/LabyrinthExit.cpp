#include "LabyrinthExit.h"

#include "Floor.h"
#include "GameObject.h"
#include "LevelManager.h"
#include "RigidBodyComponent.h"
#include "SpriteColliderComponent.h"
#include "Trigger.h"
#include "Vector.h"

namespace Roguelike {
LabyrinthExit::LabyrinthExit(MaxrEngine::Vector2Df position, int textureIndex,
                             MaxrEngine::Vector2Di size)
    : Floor(position, textureIndex, size) {
    auto exitTrigger =
        gameObject->AddComponent<MaxrEngine::SpriteColliderComponent>();
    exitTrigger->SetTrigger(true);

    auto onEnter = [](MaxrEngine::Trigger trigger) {
        LevelManager::Instance()->CheckExited(trigger, true);
        ;
    };
    exitTrigger->SubscribeTriggerEntered(onEnter);

    auto onExit = [](MaxrEngine::Trigger trigger) {
        LevelManager::Instance()->CheckExited(trigger, false);
        ;
    };
    exitTrigger->SubscribeTriggerExit(onExit);

    auto rigidBody = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
    rigidBody->SetKinematic(false);
}
}  // namespace Roguelike