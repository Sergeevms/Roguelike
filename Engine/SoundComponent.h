#pragma once
#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

#include "Component.h"
#include "EngineAPI.h"

namespace MaxrEngine {
class ENGINE_API SoundComponent : public Component {
   public:
    explicit SoundComponent(GameObject* gameObject);
    ~SoundComponent();

    void Update(float deltaTime) override;
    void Render() override;

    void SetSound(const sf::SoundBuffer& newSound);
    void SetLoop(bool newLoop);

    void SetVolume(float volume);
    void Play();
    void Stop();
    void Pause();
    void Resume();

   private:
    sf::Sound* sound;
};
}  // namespace MaxrEngine
