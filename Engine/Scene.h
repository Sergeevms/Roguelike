#pragma once
namespace MaxrEngine {
class Scene {
   public:
    virtual ~Scene() = default;
    virtual void Start() = 0;
    virtual void Restart() = 0;
    virtual void Stop() = 0;
};
}  // namespace MaxrEngine
