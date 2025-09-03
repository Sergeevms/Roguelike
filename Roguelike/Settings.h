#pragma once
#include <string>

#include "AIActor.h"
#include "Actor.h"
#include "GameLevel.h"
#include "ResourceSystem.h"
#include "Vector.h"

namespace Roguelike {
/**
 * @brief Comprehensive game settings structure
 * @details Contains all configurable parameters for game operation,
 * including rendering, resources, gameplay mechanics, and level design
 */
struct SettingsStruct {
    // Window & camera parameters
    int screenWidth;        ///< Game window width in pixels
    int screenHeight;       ///< Game window height in pixels
    std::wstring gameName;  ///< Game window title

    // Paths to files
    std::string resourcesPath;    ///< Root resources directory
    std::string soundPath;        ///< Sound assets directory
    std::string fontPath;         ///< Font assets directory
    std::string texturePath;      ///< Texture assets directory
    std::string textureMapsPath;  ///< Texture map assets directory

    MaxrEngine::ResourceSystem::TextureMapLoadingParameters
        playerTextureMap;  ///< Configuration for loading player texture map
    MaxrEngine::ResourceSystem::TextureMapLoadingParameters
        enemyTextureMap;  ///< Configuration for loading enemy texture map
    MaxrEngine::ResourceSystem::TextureMapLoadingParameters
        wallTextureMap;  ///< Configuration for loading wall texture map
    MaxrEngine::ResourceSystem::TextureMapLoadingParameters
        floorTextureMap;  ///< Configuration for loading floor texture map

    Actor::Parameters playerParameters;  ///< Player character settings
    AIActor::Parameters aiParameters;    ///< AI enemy settings

    int mapTileSize;  ///< Size of map tiles in pixels

    GameLevel::Parameters
        firstLevelParameters;      ///< Initial level generation settings
    float timeToRemoveAfterDeath;  ///< Time before removing dead entities
};

/**
 * @brief Singleton class managing game settings
 * @details Provides global access to game configuration with default values.
 * TODO: Implement serialization for saving/loading settings
 */
class Settings : public SettingsStruct {
   public:
    /**
     * @brief Render layer enumeration for depth sorting
     */
    enum class RenderLayers {
        BackGround,  ///< Background elements
        Floor,       ///< Floor tiles
        Walls,       ///< Wall structures
        Actors,      ///< Character entities
        UI1,         ///< First layer for UI elements
        UI2,         ///< Second layer for UI elements
        Debug,       ///< Debug visualization
        Count        ///< Total number of layers
    };
    /**
     * @brief Actor group identifiers for ActorRegisterSystem
     */
    enum ActorsGroups {
        Player,  ///< Player group identifier
        Enemy    ///< Enemy group identifier
    };

    /**
     * @brief Gets the singleton instance
     * @return Pointer to Settings instance
     */
    static Settings* Instance() {
        static Settings world;
        return &world;
    };

    /**
     * @brief Calculates screen center position
     * @return Vector representing screen center
     */
    MaxrEngine::Vector2Df ScreenCenter() const;
    /**
     * @brief Gets screen dimensions
     * @return Vector representing screen width and height
     */
    MaxrEngine::Vector2Df ScreenSize() const;

   private:
    static const SettingsStruct
        defaultsSettings;  ///< Default configuration values
    Settings()
        : SettingsStruct(defaultsSettings) {
          };  ///< Private constructor for singleton
    ~Settings() = default;
    Settings(const Settings&) = delete;
    Settings operator=(const Settings&) = delete;
};
};  // namespace Roguelike