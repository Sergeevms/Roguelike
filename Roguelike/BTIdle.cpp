#include "BTIdle.h"

#include <optional>
#include <string>

#include "AIBlackboard.h"
#include "AIInputComponent.h"
#include "AIPerceptionComponent.h"
#include "BTNode.h"
#include "GameObject.h"
#include "Vector.h"
namespace Roguelike {

void Roguelike::BTIdle::SetUpBlackboard(AIBlackboard* blackboard,
                                        const float timeToStay) {
    blackboard->Set(std::string(durationBBName), timeToStay);
}

BTNode::Status BTIdle::Execute(MaxrEngine::GameObject* object,
                               AIBlackboard* blackboard) {
    float timeToStay;
    auto input = object->GetComponent<AIInputComponent>();
    input->SetDirection({0, 0});
    if (blackboard->Get(std::string(durationBBName), timeToStay)) {
        std::optional<float> timeStayed;
        if (blackboard->Get(std::string(timerBBName), timeStayed) &&
            timeStayed) {
            float deltaTime;
            if (blackboard->Get(std::string(deltaTimeBBName), deltaTime)) {
                timeStayed.value() += deltaTime;
                if (*timeStayed >= timeToStay) {
                    timeStayed.reset();
                    blackboard->Set(std::string(timerBBName), timeStayed);
                    return BTNode::Status::Success;
                }
                blackboard->Set(std::string(timerBBName), timeStayed);
                return BTNode::Status::Running;
            }
        }
        timeStayed = 0.0F;
        blackboard->Set(std::string(timerBBName), timeStayed);
        return BTNode::Status::Running;
    }
    return BTNode::Status::Failure;
};

void Roguelike::BTLookAroundIdle::SetUpBlackboard(AIBlackboard* blackboard,
                                                  const float timeToRotate) {
    blackboard->Set(std::string(durationBBName), timeToRotate);
}
BTNode::Status BTLookAroundIdle::Execute(MaxrEngine::GameObject* object,
                                         AIBlackboard* blackboard) {
    float timeToRotate;
    if (blackboard->Get(std::string(durationBBName), timeToRotate)) {
        std::optional<float> timeRotated;
        if (blackboard->Get(std::string(timerBBName), timeRotated) &&
            timeRotated) {
            float deltaTime;
            if (blackboard->Get(std::string(deltaTimeBBName), deltaTime)) {
                if (auto* perception =
                        object->GetComponent<AIPerceptionComponent>()) {
                    const float rotationAngle =
                        360.0F / timeToRotate * deltaTime;
                    auto newDirection = perception->GetVisionDirection();
                    MaxrEngine::Rotate(newDirection, rotationAngle);
                    perception->SetVisionDirection(newDirection);
                }

                timeRotated.value() += deltaTime;
                if (*timeRotated >= timeToRotate) {
                    timeRotated.reset();
                    blackboard->Set(std::string(timerBBName), timeRotated);
                    return BTNode::Status::Success;
                }
                blackboard->Set(std::string(timerBBName), timeRotated);
                return BTNode::Status::Running;
            }
        }
        timeRotated = 0.0F;
        blackboard->Set(std::string(timerBBName), timeRotated);
        return BTNode::Status::Running;
    }
    return BTNode::Status::Failure;
}
}  // namespace Roguelike