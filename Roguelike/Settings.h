#pragma once
#include <string>

#include "AIActor.h"
#include "Actor.h"
#include "LabyrinthBuilder.h"
#include "ResourceSystem.h"
#include "Vector.h"

namespace Roguelike {
/** Struct storing game settings
 */
struct SettingsStruct {
    // Window & camera parameters
    int screenWidth;
    int screenHeight;
    std::wstring gameName;

    // Paths to files
    std::string resourcesPath;
    std::string soundPath;
    std::string fontPath;
    std::string texturePath;
    std::string textureMapsPath;

    MaxrEngine::ResourceSystem::TextureMapLoadingParameters playerTextureMap;
    MaxrEngine::ResourceSystem::TextureMapLoadingParameters enemyTextureMap;
    MaxrEngine::ResourceSystem::TextureMapLoadingParameters wallTextureMap;
    MaxrEngine::ResourceSystem::TextureMapLoadingParameters floorTextureMap;

    Actor::Parameters playerParameters;
    AIActor::Parameters aiParameters;

    int mapTileSize;

    LabyrinthBuilder::Parameters labyrinthParameters;
};

/** Singleton class storing current game settings
 *   TODO(MaxrRusich) : serialization
 */
class Settings : public SettingsStruct {
   public:
    static Settings* Instance() {
        static Settings world;
        return &world;
    };
    MaxrEngine::Vector2Df ScreenCenter() const;
    MaxrEngine::Vector2Df ScreenSize() const;

   private:
    static const SettingsStruct defaultsSettings;
    Settings() : SettingsStruct(defaultsSettings) {};
    ~Settings() = default;
    Settings(const Settings&) = delete;
    Settings operator=(const Settings&) = delete;
};
/** Enum to define Actors group*/
enum ActorsGroups { PlayerGroup, EnemyGroup };
};  // namespace Roguelike