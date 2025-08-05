#include "pch.h"

#include "SpriteAnimationComponent.h"

#include "Component.h"
#include "GameObject.h"
#include "ResourceSystem.h"
#include "SpriteRendererComponent.h"

namespace MaxrEngine {
SpriteAnimationComponent::SpriteAnimationComponent(GameObject* gameObject)
    : Component(gameObject) {
    rendererComponent =
        gameObject->GetComponentSharedPtr<SpriteRendererComponent>();
    // Check that rendererComponent available. If not, remove component
    if (rendererComponent.expired()) {
        gameObject->RemoveComponent(this);
        return;
    }
}
void SpriteAnimationComponent::Update(float deltaTime) {
    timer += deltaTime;
    // Check if we need to change frame
    if (timer >= timePerFrame) {
        timer = 0.0F;
        currentFrame++;
        if (currentFrame >= framesTextures.size()) {
            if (currentAnimationName == nextAnimationName) {
                // If next animation is same, just reset timers
                ResetAnimation();
            } else {
                currentAnimationName = nextAnimationName;
                StartCurrentAnimation();
            }
            nextAnimationName = defaultAnimationName;
        }
        // Update texture in renderer
        auto renderer = rendererComponent.lock();
        if (renderer != nullptr && currentFrame < framesTextures.size() &&
            framesTextures[currentFrame] != nullptr) {
            renderer->SetTexture(*framesTextures[currentFrame]);
        }
    }
}
void SpriteAnimationComponent::Render() {}
void SpriteAnimationComponent::AddAnimation(const std::string& animationName,
                                            const Animation& animation,
                                            bool isDefault) {
    animations[animationName] = animation;
    if (isDefault || defaultAnimationName == "") {
        defaultAnimationName = animationName;
    }
}
void SpriteAnimationComponent::RemoveAnimation(
    const std::string& animationName) {
    auto animationIterator = animations.find(animationName);
    if (animationIterator != animations.end()) {
        animations.erase(animationIterator);
    }
}
void SpriteAnimationComponent::StartAnimation(
    const std::string& animationName) {
    currentAnimationName = animationName;
    nextAnimationName = defaultAnimationName;
    StartCurrentAnimation();
}
void SpriteAnimationComponent::SetNextAnimation(
    const std::string& animationName) {
    nextAnimationName = animationName;
}
void SpriteAnimationComponent::StartCurrentAnimation() {
    // Check if have animation named in currentAnimationName
    auto animationIter = animations.find(currentAnimationName);
    if (animationIter != animations.end()) {
        auto& animation = animationIter->second;
        // Update framesTextures for current animation
        framesTextures.clear();
        framesTextures.reserve(animation.frameIDs.size());
        for (auto& frameID : animation.frameIDs) {
            framesTextures.push_back(
                ResourceSystem::Instance()->GetTextureMapElementShared(
                    animation.textureMapName, frameID));
        }
        // Update time per frame
        timePerFrame =
            animation.time / static_cast<float>(animation.frameIDs.size());
        // Reset currentFrame and timer
        ResetAnimation();
    }
}
void SpriteAnimationComponent::ResetAnimation() {
    timer = 0.0F;
    currentFrame = 0;
}
}  // namespace MaxrEngine
