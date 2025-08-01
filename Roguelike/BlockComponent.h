#pragma once
#include "SFML/Graphics/Color.hpp"

#include "Component.h"
#include "Vector.h"

namespace Roguelike {
/** Block component - blocks damage depending on input. In blocking state
 * affects movement speed*/
class BlockComponent : public MaxrEngine::Component {
   public:
    struct Parameters {
        /** Damage reduction in 0.0F - 1.0F range */
        float damageReduction;
        /** Coefficient in 0.0F - 1.0F range applied to movement */
        float speedCoefficient;
        /** Local blocking icon position*/
        MaxrEngine::Vector2Df centerOffset;
        /** Icon radius*/
        float iconRadius;
        /** Icon color*/
        sf::Color iconColor;
    };
    explicit BlockComponent(MaxrEngine::GameObject* gameObject,
                            const Parameters& parameters = defaultParameters);
    /** Updates isBlocking depending on input. Changing moving speed if
     * isBlocking state changes*/
    void Update(float deltaTime) override;
    /** Draw icon if isBlocking*/
    void Render() override;
    /** Return damage gone throw block*/
    float ApplyDamage(const float damage) const;
    /** Return true if blocking*/
    bool GetIsBlocking() const;

   private:
    const static Parameters defaultParameters;
    /** Damage reduction in 0.0F - 1.0F range 1.0F for absorbing 100% at each
     * damage applies, 0.1F for absorbing 10% of damage applied and 90% moving
     * throw armor */
    float damageReduction;
    /** Coefficient in 0.0F - 1.0F range applied to movement speed when block is
     * active*/
    float speedCoefficient;
    /** Is currently blocking*/
    bool isBlocking = false;
    /** Local blocking icon position*/
    MaxrEngine::Vector2Df centerOffset;
    /** Icon radius*/
    float iconRadius;
    /** Icon color*/
    sf::Color iconColor;
};
}  // namespace Roguelike
