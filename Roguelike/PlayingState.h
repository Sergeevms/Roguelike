#pragma once
#include "BaseState.h"
#include <unordered_map>
#include <memory>
#include "IListDrawable.h"
#include "Utility.h"

namespace Roguelike
{
    class PlayingState :
        public BaseState
    {
    public:
        PlayingState();
        virtual ~PlayingState() = default;
        virtual void Draw(sf::RenderWindow& window) const override;
        virtual void Update(const float deltaTime) override;
        virtual void Init() override;
    private:
        ListDrawableText toBeDone;
        ListDrawableText pressEsc;
        TextStyle textStyle;
    };
}