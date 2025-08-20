#pragma once
#include "EngineAPI.h"
namespace MaxrEngine {
class ENGINE_API Engine {
   public:
    static Engine* Instance();

    void Run();

   private:
    Engine();
    ~Engine() = default;
    Engine(const Engine& app) = delete;
    Engine& operator=(const Engine&) = delete;
};
}  // namespace MaxrEngine
