#pragma once
#include "EngineAPI.h"
namespace MaxrEngine {
class IFixedUpdateSystem {
   public:
    static constexpr float defaultFixedUpdateTime = 0.015F;
    ENGINE_API IFixedUpdateSystem();
    ENGINE_API virtual ~IFixedUpdateSystem();
    ENGINE_API float GetFixedUpdateTime() const;
    ENGINE_API void SetFixedUpdateTime(const float newFixedUpdateTime);
    ENGINE_API virtual void Update() = 0;

   protected:
    float fixedUpdateTime = defaultFixedUpdateTime;
};
}  // namespace MaxrEngine
