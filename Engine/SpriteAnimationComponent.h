#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "SFML/Graphics/Texture.hpp"

#include "Component.h"
#include "EngineAPI.h"
#include "GameObject.h"
#include "SpriteRendererComponent.h"

namespace MaxrEngine {
/** Struct holding information about animation - texture map name,
 * framesTextures from texture map, animation time length, direction of sprites
 */
struct Animation {
    /** Name of texture map stored in ResourceSystem*/
    std::string textureMapName;
    /** Vector storing framesTextures ID in texture map*/
    std::vector<int> frameIDs;
    /** Time needed to finish animation*/
    float time;
    /** Is animation sprite directed to rigth*/
    bool isRightDirected;
    /** Animation with lower priority wouldn change current in StartAnimation*/
    int priority;
    /** Animation wouldn't stop until switched to another*/
    bool isLoop = false;
};
/** Base animation component. Require SpriteRendererComponent to work.
 * Allows to store several animation by their name, one of which can be marked
 * as default Can set next animation to play by SetNextAnimation or immidiatly
 * start animation by StartAnimation If no next animation setted by the time
 * current is over, switches to default animation
 */
class SpriteAnimationComponent : public Component {
   public:
    /** Constructor. Checks if SpriteRendererComponent available for gameObject,
     * removes SpriteAnimationComponent otherwise*/
    ENGINE_API explicit SpriteAnimationComponent(GameObject* gameObject);
    /** Updates timers, frame, currentAnimationName if needed*/
    ENGINE_API void Update(float deltaTime) override;
    /** Overrides stored in component animation by name animationName. Updates
     * defaultAnimationName if isDefault is true or defaultAnimation not setted
     * yet
     */
    ENGINE_API void AddAnimation(const std::string& animationName,
                                 const Animation& animation,
                                 bool isDefault = false);
    /** Remove animation from component*/
    ENGINE_API void RemoveAnimation(const std::string& animationName);

    /** Imideatly change current animation, set next animation to default*/
    ENGINE_API void StartAnimation(const std::string& animationName,
                                   const bool ignorePriority = false);

   protected:
    /** Updates timePerFrame, framesTextures, resets timer and curretFrame*/
    void StartCurrentAnimation();
    /** Resets timer and curretFrame */
    void ResetAnimation();
    /** Update SpriteRendererComponent texture accroding current frame*/
    void UpdateRendereTrexture() const;
    /** Stores animations*/
    std::unordered_map<std::string, Animation> animations;
    /** Animation played by default*/
    std::string defaultAnimationName;
    /** Currently played animation name*/
    std::string currentAnimationName;
    /** Stores pointer to Textures from ResourceSystem for current animation*/
    std::vector<const sf::Texture*> framesTextures;
    /** Pointer to GameObject SpriteRendererComponent*/
    std::weak_ptr<SpriteRendererComponent> rendererComponent;
    /** Current animation time per frame*/
    float timePerFrame = 0.0F;
    /** Time since frame was changed*/
    float timer = 0.0F;
    /** Current frame number in current animation*/
    int currentFrame = 0;
    /** Is current textures is rightDirected*/
    bool isRigthDirected = true;
    /** Animation wouldn't stop until switched to another*/
    bool isLoop = true;
};

}  // namespace MaxrEngine