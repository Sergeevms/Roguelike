#include "PlayerActor.h"

#include "Actor.h"
#include "CameraComponent.h"
#include "KeyboardInputComponent.h"
#include "LevelManager.h"
#include "PlayerAttackComponent.h"
#include "RenderSystem.h"
#include "Settings.h"
#include "Vector.h"

namespace Roguelike {
PlayerActor::PlayerActor(const Actor::Parameters& parameters,
                         const MaxrEngine::Vector2Df& position)
    : Actor(parameters, position) {
    auto inputComponent =
        gameObject->AddComponent<MaxrEngine::KeyboardInputComponent>();
    auto attackComponent = gameObject->AddComponent<PlayerAttackComponent>(
        parameters.attackComponentParameters);
    inputComponent->AddObserver(attackComponent);
    inputComponent->AddObserver(LevelManager::Instance());
    auto playerCamera = gameObject->AddComponent<MaxrEngine::CameraComponent>();
    playerCamera->SetWindow(
        &MaxrEngine::RenderSystem::Instance()->GetMainWindow());
    auto* settings = Settings::Instance();
    playerCamera->SetBaseResolution(settings->screenWidth,
                                    settings->screenHeight);
}
}  // namespace Roguelike
