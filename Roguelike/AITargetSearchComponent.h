#pragma once
#include <Component.h>

namespace Roguelike
{
    class AITargetSearchComponent :
        public MaxrEngine::Component
    {
    public:
        AITargetSearchComponent(MaxrEngine::GameObject* gameObject);

        virtual void Update(float deltaTime);
        virtual void Render();

        void SetSearchTarget(MaxrEngine::GameObject* newTarget);
        void SetDetectionRange(float newDetectionRange);
    private:
        MaxrEngine::GameObject* target = nullptr;
        float detectionRange = 0;
    };
}

