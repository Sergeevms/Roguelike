#include "Settings.h"

#include "DefaultActorsSettings.h"
#include "Utility.h"
#include "Vector.h"

namespace Roguelike {
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
    .enemyTextureMap = {.name = "EnemyTextures",
                        .sourcePath = "Resources\\TextureMaps\\Enemy.png",
                        .elementPixelSize = {96, 96},
                        .totalElements = 15,
                        .isSmooth = false},
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

    .playerParameters = DefaultSettings::defaultPlayerParameters,
    .aiParameters = DefaultSettings::AIActorParameters,

    .mapTileSize = 150,
    .firstLevelParameters = {.builderParameters = {.width = 5,
                                                   .heigth = 5,
                                                   .isAdjustingSizeAndStart =
                                                       true,
                                                   .randSeed = -1},
                             .enemyCount = 1},
    .labyrinthParameters = {.width = 11,
                            .heigth = 11,
                            .isAdjustingSizeAndStart = true,
                            .randSeed = -1},
    .timeToRemoveAfterDeath = 4.0F};

MaxrEngine::Vector2Df Settings::ScreenCenter() const {
    return Half(ScreenSize());
}

MaxrEngine::Vector2Df Settings::ScreenSize() const {
    return MaxrEngine::Vector2Df(
        {static_cast<float>(screenWidth), static_cast<float>(screenHeight)});
}
}  // namespace Roguelike
