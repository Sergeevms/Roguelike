#include "PlayerActor.h"

#include "Actor.h"
#include "CameraComponent.h"
#include "KeyboardInputComponent.h"
#include "PlayerAttackComponent.h"
#include "RenderSystem.h"
#include "Settings.h"

namespace Roguelike {
PlayerActor::PlayerActor(const Actor::Parameters& parameters,
                         const MaxrEngine::Vector2Df& position)
    : Actor(parameters, position) {
    auto inputComponent =
        gameObject->AddComponent<MaxrEngine::KeyboardInputComponent>();
    auto attackComponent = gameObject->AddComponent<PlayerAttackComponent>();
    inputComponent->AddObserver(attackComponent);

    auto playerCamera = gameObject->AddComponent<MaxrEngine::CameraComponent>();
    playerCamera->SetWindow(
        &MaxrEngine::RenderSystem::Instance()->GetMainWindow());
    auto* settings = Settings::Instance();
    playerCamera->SetBaseResolution(settings->screenWidth,
                                    settings->screenHeight);
}
}  // namespace Roguelike
