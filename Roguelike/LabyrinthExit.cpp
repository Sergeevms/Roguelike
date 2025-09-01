#include "LabyrinthExit.h"

#include <memory>

#include "ColliderDebugRender.h"
#include "Floor.h"
#include "GameObject.h"
#include "LevelCompleteCondition.h"
#include "LevelManager.h"
#include "RigidBodyComponent.h"
#include "Settings.h"
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
    gameObject->AddComponent<MaxrEngine::ColliderDebugRender>(
        exitTrigger, static_cast<int>(Settings::RenderLayers::Debug));

    auto onEnter = [](MaxrEngine::Trigger trigger) {
        auto conditions = LevelManager::Instance()->GetCompleteConditions();
        for (auto condition : conditions) {
            if (auto exitCondition =
                    std::dynamic_pointer_cast<ExitReached>(condition))
                exitCondition->CheckExited(trigger, true);
        }
    };
    exitTrigger->SubscribeTriggerEntered(onEnter);

    auto onExit = [](MaxrEngine::Trigger trigger) {
        auto conditions = LevelManager::Instance()->GetCompleteConditions();
        for (auto condition : conditions) {
            if (auto exitCondition =
                    std::dynamic_pointer_cast<ExitReached>(condition))
                exitCondition->CheckExited(trigger, false);
        }
    };
    exitTrigger->SubscribeTriggerExit(onExit);

    auto rigidBody = gameObject->AddComponent<MaxrEngine::RigidBodyComponent>();
    rigidBody->SetKinematic(false);
}
}  // namespace Roguelike