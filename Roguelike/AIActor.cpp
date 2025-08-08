#include "AIActor.h"

#include "AIAttackComponent.h"
#include "AIBlackboard.h"
#include "AIChaseTargetComponent.h"
#include "AIInputComponent.h"
#include "AIPerceptionComponent.h"
#include "AITargetSelector.h"
#include "Actor.h"
#include "PerceptionComponentDebugDraw.h"
#include "Vector.h"

namespace Roguelike {
AIActor::AIActor(const Parameters& parameters,
                 const MaxrEngine::Vector2Df& position)
    : Actor(parameters.baseActorParameters, position) {
    auto input = gameObject->AddComponent<MaxrEngine::AIInputComponent>();
    auto enemyChase = gameObject->AddComponent<AIChaseTargetComponent>(
        parameters.chaseTargetParameters);
    gameObject->AddComponent<AIBlackboard>();
    auto perception = gameObject->AddComponent<AIPerceptionComponent>(
        parameters.perceptionParameters);
    input->AddObserver(perception);
    auto perceptionDebugDraw =
        gameObject->AddComponent<PerceptionComponentDebugDraw>();
    auto targetSelector = gameObject->AddComponent<AITargetSelector>();
    perception->AddObserver(targetSelector);
    gameObject->AddComponent<AIAttackComponent>(
        parameters.baseActorParameters.attackComponentParameters);
}
}  // namespace Roguelike