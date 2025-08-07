#include "Settings.h"

#include "SFML/Graphics/Color.hpp"

#include "Utility.h"
#include "Vector.h"

namespace Roguelike {
constexpr float attackWindup = 0.5F;
const SettingsStruct Settings::defaultsSettings{

    .screenWidth = 1280,
    .screenHeight = 720,
    .gameName = L"Roguelike",

    .resourcesPath = "Resources\\",
    .soundPath = "Resources\\Sounds\\",
    .fontPath = "Resources\\Fonts\\",
    .texturePath = "Resources\\Textures\\",
    .textureMapsPath = "Resources\\TextureMaps\\",

    .playerTextureMap = {.name = "PlayerTextures",
                         .sourcePath = "Resources\\TextureMaps\\Player.png",
                         .elementPixelSize = {100, 80},
                         .totalElements = 16,
                         .isSmooth = true},
    .playerIdleAnimation = {.textureMapName = "PlayerTextures",
                            .frameIDs = {0, 1, 2, 3},
                            .time = 0.8F,
                            .isRightDirected = false,
                            .priority = 0,
                            .isLoop = true},
    .playerWalkingAnimation = {.textureMapName = "PlayerTextures",
                               .frameIDs = {4, 5, 6, 7, 8, 9},
                               .time = 1.0F,
                               .isRightDirected = false,
                               .priority = 0,
                               .isLoop = true},
    .playerAttackWindupAnimation = {.textureMapName = "PlayerTextures",
                                    .frameIDs = {10, 11},
                                    .time = attackWindup,
                                    .isRightDirected = false,
                                    .priority = 2},
    .playerAttackAnimation = {.textureMapName = "PlayerTextures",
                              .frameIDs = {12, 13, 14},
                              .time = 2.0F * attackWindup,
                              .isRightDirected = false,
                              .priority = 2},

    .playerDeathAnimation = {.textureMapName = "PlayerTextures",
                             .frameIDs = {14, 15},
                             .time = 1.0F,
                             .isRightDirected = false,
                             .priority = 1},
    .playerDeadAnimation = {.textureMapName = "PlayerTextures",
                            .frameIDs = {15},
                            .time = 3600.0F,
                            .isRightDirected = false,
                            .priority = 100},
    .enemyTextureMap = {.name = "EnemyTextures",
                        .sourcePath = "Resources\\TextureMaps\\Enemy.png",
                        .elementPixelSize = {96, 96},
                        .totalElements = 15,
                        .isSmooth = false},
    .enemyIdleAnimation = {.textureMapName = "EnemyTextures",
                           .frameIDs = {0, 1},
                           .time = 0.8F,
                           .isRightDirected = true,
                           .priority = 0,
                           .isLoop = true},
    .enemyWalkingAnimation = {.textureMapName = "EnemyTextures",
                              .frameIDs = {5, 6, 7, 8},
                              .time = 1.0F,
                              .isRightDirected = true,
                              .priority = 0,
                              .isLoop = true},
    .enemyAttackWindupAnimation = {.textureMapName = "EnemyTextures",
                                   .frameIDs = {10, 11},
                                   .time = attackWindup,
                                   .isRightDirected = true,
                                   .priority = 2},
    .enemyAttackAnimation = {.textureMapName = "EnemyTextures",
                             .frameIDs = {12, 13, 14},
                             .time = 2.0F * attackWindup,
                             .isRightDirected = true,
                             .priority = 2},
    .wallTextureMap = {.name = "WallTextures",
                       .sourcePath = "Resources\\TextureMaps\\Wall.png",
                       .elementPixelSize = {16, 16},
                       .totalElements = 48,
                       .isSmooth = false},
    .floorTextureMap = {.name = "FloorTextures",
                        .sourcePath = "Resources\\TextureMaps\\Floor.png",
                        .elementPixelSize = {16, 16},
                        .totalElements = 49,
                        .isSmooth = false},
    .playerSize = 70,
    .playerSpeed = 400.0F,

    .enemySpeed = 200.0F,

    .enemyPerceptionParameters = {.visionAngle = 145.0F,
                                  .visionRadius = 300.0F,
                                  .visionDirectionX = -1.0F,
                                  .visionDirectionY = 0.0F,
                                  .senseRadius = 150.0F},
    .enemyChaseMaxRadius = 300.0F,
    .enemyChaseMinRadius = 75.0F,

    .mapTileSize = 150,

    .playerHealth = 200.0F,
    .enemyHealth = 100.0F,
    .armorDamageReduction = 0.75F,

    .playerAtackParameters = {.startupTime = attackWindup,
                              .cooldown = 2.0F,
                              .damage = 30.0F,
                              .range = 110.0F},
    .enemyAtackParameters = {.startupTime = 0.2F,
                             .cooldown = 2.0F,
                             .damage = 25.0F,
                             .range = 100.0F},

    .healthBarParameters = {.centerOffset = {0.0F, 35.0F},
                            .barSize = {32.0F, 5.0F},
                            .barColor = sf::Color(255, 0, 0),
                            .borderSize = -1.0F},

    .armorBarParameters = {.centerOffset = {0.0F, 41.0F},
                           .barSize = {32.0F, 5.0F},
                           .barColor = sf::Color(255, 255, 0),
                           .borderSize = -1.0F},

    .labyrinthParameters = {.width = 11,
                            .heigth = 11,
                            .isAdjustingSizeAndStart = true,
                            .randSeed = -1},
    .playerBlockParameters = {.damageReduction = 1.0F,
                              .speedCoefficient = 0.1F,
                              .iconCenterOffset = {-35.0F, 30.0F},
                              .iconRadius = 6.0F,
                              .iconColor = sf::Color(0, 255, 0)}};

MaxrEngine::Vector2Df Settings::ScreenCenter() const {
    return Half(ScreenSize());
}

MaxrEngine::Vector2Df Settings::ScreenSize() const {
    return MaxrEngine::Vector2Df(
        {static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
}
float Settings::PlayerSizeF() const { return static_cast<float>(playerSize); }
}  // namespace Roguelike
