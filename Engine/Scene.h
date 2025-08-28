#pragma once
namespace MaxrEngine {
/**
 * @brief Base class for game scenes
 * @details Defines the interface for scenes that can be started,
 * restarted, and stopped
 */
class Scene {
   public:
    virtual ~Scene() = default;
    /**
     * @brief Starts the scene
     */
    virtual void Start() = 0;
    /**
     * @brief Restarts the scene
     */
    virtual void Restart() = 0;
    /**
     * @brief Stops the scene
     */
    virtual void Stop() = 0;
};
}  // namespace MaxrEngine
