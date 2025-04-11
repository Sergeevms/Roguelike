#include "DeveloperLevel.h"
#include "..\Engine\GameWorld.h"

namespace Roguelike
{
    void DeveloperLevel::Start() 
    {
        player = std::make_shared<Player>();
    }

    void DeveloperLevel::Restart()
    {
        Stop();
        Start();
    }

    void DeveloperLevel::Stop()
    {
        MaxrEngine::GameWorld::Instance()->Clear();
    }
}