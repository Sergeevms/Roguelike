#pragma once

namespace MaxrEngine {
class IFixedUpdateSystem {
   public:
    static constexpr float defaultFixedUpdateTime = 0.015F;
    IFixedUpdateSystem();
    virtual ~IFixedUpdateSystem();
    float GetFixedUpdateTime() const;
    void SetFixedUpdateTime(const float newFixedUpdateTime);
    virtual void Update() = 0;

   protected:
    float fixedUpdateTime = defaultFixedUpdateTime;
};
}  // namespace MaxrEngine
