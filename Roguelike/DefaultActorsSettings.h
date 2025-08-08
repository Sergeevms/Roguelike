#pragma once
#include "Actor.h"
#include "Settings.h"
namespace Roguelike {
namespace DefaultSettings {

constexpr int defaultActorSpriteSize = 70;
constexpr float defaultActorSpriteSizeF = defaultActorSpriteSize;
constexpr float defaultBarHeigth = 5.0F;
constexpr float defaultBarBorderSize = -1.0F;
constexpr float attackWindup = 0.5F;

const Actor::Parameters defaultPlayerParameters = {
    .actorGroupID = ActorsGroups::PlayerGroup,
    .maxHealthAmount = 200.0F,
    .healthBarParameters = {.centerOffset = {0.0F,
                                             (defaultActorSpriteSizeF / 2) +
                                                 defaultBarHeigth},
                            .barSize = {defaultActorSpriteSizeF,
                                        defaultBarHeigth},
                            .barColor = sf::Color(255, 0, 0),
                            .borderSize = defaultBarBorderSize},
    .movementSpeed = 400.0F,
    .spriteSize = {defaultActorSpriteSize, defaultActorSpriteSize},
    .defaultAnimationName = "Idle",
    .animations = {{"Idle",
                    {.textureMapName = "PlayerTextures",
                     .frameIDs = {0, 1, 2, 3},
                     .time = 0.8F,
                     .isRightDirected = false,
                     .priority = 0,
                     .isLoop = true}},
                   {"Walk",
                    {.textureMapName = "PlayerTextures",
                     .frameIDs = {4, 5, 6, 7, 8, 9},
                     .time = 1.0F,
                     .isRightDirected = false,
                     .priority = 0,
                     .isLoop = true}},
                   {"Attack windup",
                    {.textureMapName = "PlayerTextures",
                     .frameIDs = {10, 11},
                     .time = attackWindup,
                     .isRightDirected = false,
                     .priority = 2}},
                   {"Attack",
                    {.textureMapName = "PlayerTextures",
                     .frameIDs = {12, 13, 14},
                     .time = 2.0F * attackWindup,
                     .isRightDirected = false,
                     .priority = 2}},
                   {"Death",
                    {.textureMapName = "PlayerTextures",
                     .frameIDs = {14, 15},
                     .time = 1.0F,
                     .isRightDirected = false,
                     .priority = 1}},
                   {"Dead",
                    {.textureMapName = "PlayerTextures",
                     .frameIDs = {15},
                     .time = 3600.0F,
                     .isRightDirected = false,
                     .priority = 100}}},
    .haveBlock = true,
    .blockParameters = {.damageReduction = 1.0F,
                        .speedCoefficient = 0.1F,
                        .iconCenterOffset = {-35.0F, 30.0F},
                        .iconRadius = 6.0F,
                        .iconColor = sf::Color(0, 255, 0)},
    .haveArmor = true,
    .armorParameters = {.maxArmorPoints = 100.0F, .damageReduction = 0.75F},
    .armorBarParameters = {.centerOffset = {0.0F,
                                            (defaultActorSpriteSizeF / 2) +
                                                (2 * defaultBarHeigth)},
                           .barSize = {defaultActorSpriteSizeF,
                                       defaultBarHeigth},
                           .barColor = sf::Color(255, 255, 0),
                           .borderSize = defaultBarBorderSize},
    .attackComponentParameters = {.startupTime = attackWindup,
                                  .cooldown = 3.0F,
                                  .damage = 30.0F,
                                  .range = 110.0F},
    .actorName = "player"};
};  // namespace DefaultSettings
}  // namespace Roguelike