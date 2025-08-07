#pragma once
#include <string>

#include "AttackComponent.h"
#include "BarComponent.h"
#include "BlockComponent.h"
#include "LabyrinthBuilder.h"
#include "PerceptionComponent.h"
#include "ResourceSystem.h"
#include "SpriteAnimationComponent.h"
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
    MaxrEngine::Animation playerIdleAnimation;
    MaxrEngine::Animation playerWalkingAnimation;
    MaxrEngine::Animation playerAttackWindupAnimation;
    MaxrEngine::Animation playerAttackAnimation;
    MaxrEngine::Animation playerDeathAnimation;
    MaxrEngine::Animation playerDeadAnimation;
    int playerSize;
    float playerSpeed;
    float enemySpeed;
    PerceptionComponent::Parameters enemyPerceptionParameters;
    float enemyChaseMaxRadius;
    float enemyChaseMinRadius;
    int mapTileSize;

    float playerHealth;
    float enemyHealth;
    float armorDamageReduction;

    AttackComponent::Parameters playerAtackParameters;
    AttackComponent::Parameters enemyAtackParameters;

    BarComponent::Parameters healthBarParameters;
    BarComponent::Parameters armorBarParameters;

    LabyrinthBuilder::Parameters labyrinthParameters;

    BlockComponent::Parameters playerBlockParameters;
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
    float PlayerSizeF() const;

   private:
    static const SettingsStruct defaultsSettings;
    Settings()
        : SettingsStruct(defaultsSettings) {

          };
    ~Settings() = default;
    Settings(const Settings&) = delete;
    Settings operator=(const Settings&) = delete;
};
/** Enum to define Actors group*/
enum ActorsGroups { PlayerGroup, EnemyGroup };
};  // namespace Roguelike