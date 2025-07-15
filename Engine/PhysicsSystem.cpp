#include "pch.h"

#include "PhysicsSystem.h"

#include <iostream>

#include "ColliderComponent.h"
#include "GameObject.h"
#include "RigidBodyComponent.h"

namespace MaxrEngine {
PhysicsSystem* PhysicsSystem::Instance() {
    static PhysicsSystem physicSystem;
    return &physicSystem;
}

void PhysicsSystem::Update() {
    for (int i = 0; i < colliders.size(); ++i) {
        auto body =
            colliders[i]->GetGameObject()->GetComponent<RigidBodyComponent>();

        if (body->GetKinematic()) {
            continue;
        }

        for (int j = 0; j < colliders.size(); ++j) {
            if (i == j) {
                continue;
            }

            sf::FloatRect intersection;
            if (colliders[i]->bounds.intersects(colliders[j]->bounds,
                                                intersection)) {
                std::ostringstream message;
                if (colliders[i]->isTrigger != colliders[j]->isTrigger) {
                    if (triggersEnteredPair.find(colliders[i]) ==
                            triggersEnteredPair.end() &&
                        triggersEnteredPair.find(colliders[j]) ==
                            triggersEnteredPair.end()) {
                        message << "Entered trigger " << colliders[i] << " "
                                << colliders[j];
                        LOG_INFO(message.str());
                        auto trigger = new Trigger(colliders[i], colliders[j]);
                        colliders[i]->OnTriggerEntered(*trigger);
                        colliders[j]->OnTriggerEntered(*trigger);
                        delete trigger;

                        triggersEnteredPair.emplace(colliders[i], colliders[j]);
                    }
                } else if (!colliders[i]->isTrigger) {
                    float intersectionWidth = intersection.width;
                    float intersectionHeight = intersection.height;
                    Vector2Df intersectionPosition = {
                        intersection.left - 0.5f * intersectionWidth,
                        intersection.top - 0.5f * intersectionHeight};

                    Vector2Df aPosition = {colliders[i]->bounds.left,
                                           colliders[i]->bounds.top};

                    auto aTransform = colliders[i]
                                          ->GetGameObject()
                                          ->GetComponent<TransformComponent>();

                    if (intersectionWidth > intersectionHeight) {
                        if (intersectionPosition.y > aPosition.y) {
                            aTransform->MoveBy(0.f, -intersectionHeight);
                            message << "Top collision " << colliders[i] << " "
                                    << colliders[j];
                            LOG_INFO(message.str());
                        } else {
                            aTransform->MoveBy(0.f, intersectionHeight);
                            message << "Bottom collision " << colliders[i]
                                    << " " << colliders[j];
                            LOG_INFO(message.str());
                        }
                    } else {
                        if (intersectionPosition.x > aPosition.x) {
                            aTransform->MoveBy(-intersectionWidth, 0.f);
                            message << "Rigth collision " << colliders[i] << " "
                                    << colliders[j];
                            LOG_INFO(message.str());
                        } else {
                            aTransform->MoveBy(intersectionWidth, 0.f);
                            message << "Left collision " << colliders[i] << " "
                                    << colliders[j];
                            LOG_INFO(message.str());
                        }
                    }

                    auto collision =
                        new Collision(colliders[i], colliders[j], intersection);
                    colliders[i]->OnCollision(*collision);
                    colliders[j]->OnCollision(*collision);
                    delete collision;
                }
            }

            for (auto triggeredPair = triggersEnteredPair.cbegin(),
                      nextTriggeredPair = triggeredPair;
                 triggeredPair != triggersEnteredPair.cend();
                 triggeredPair = nextTriggeredPair) {
                ++nextTriggeredPair;
                if (!triggeredPair->first->bounds.intersects(
                        triggeredPair->second->bounds)) {
                    std::ostringstream message;
                    message << "Exited trigger " << triggeredPair->first << " "
                            << triggeredPair->second;
                    auto trigger = new Trigger(triggeredPair->first,
                                               triggeredPair->second);
                    triggeredPair->first->OnTriggerExit(*trigger);
                    triggeredPair->second->OnTriggerExit(*trigger);
                    delete trigger;

                    triggersEnteredPair.erase(triggeredPair);
                }
            }
        }
    }
}

void PhysicsSystem::Subscribe(ColliderComponent* collider) {
    std::ostringstream message;
    message << "Subscribe collider " << collider;
    LOG_INFO(message.str());
    colliders.push_back(collider);
}

void PhysicsSystem::Unsubscribe(ColliderComponent* collider) {
    std::ostringstream message;
    message << "Unsubscribe collider " << collider;
    LOG_INFO(message.str());
    colliders.erase(std::remove_if(colliders.begin(), colliders.end(),
                                   [collider](ColliderComponent* obj) {
                                       return collider == obj;
                                   }),
                    colliders.end());
}
}  // namespace MaxrEngine