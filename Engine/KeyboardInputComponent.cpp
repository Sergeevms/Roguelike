#include "pch.h"

#include "KeyboardInputComponent.h"

#include "SFML/Window/Keyboard.hpp"

#include "Component.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "Logger.h"

namespace MaxrEngine {
KeyboardInputComponent::KeyboardInputComponent(GameObject* gameObject)
    : InputComponent(gameObject) {}
// NOLINTBEGIN(misc-unused-parameters) : inhereted method with parameter
void KeyboardInputComponent::Update(float deltaTime) {
    verticalAxis = 0.0F;
    horizontalAxis = 0.0F;
    attack = false;
    block = false;
    levelTransfer = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        LOG_INFO("Forward input");
        verticalAxis += 1.0F;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        LOG_INFO("Backward input");
        verticalAxis -= 1.0F;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        LOG_INFO("Right input");
        horizontalAxis += 1.0F;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        LOG_INFO("Left input");
        horizontalAxis -= 1.0F;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        LOG_INFO("Attack input");
        attack = true;
        Emit();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        LOG_INFO("Block input");
        block = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
        LOG_INFO("Level transfer input");
        levelTransfer = true;
        Emit();
    }
}
// NOLINTEND(misc-unused-parameters)
}  // namespace MaxrEngine