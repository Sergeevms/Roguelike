#pragma once
#include "SFML/Audio/Music.hpp"

#include "Component.h"

namespace MaxrEngine {
class MusicComponent : public Component {
   public:
    explicit MusicComponent(GameObject* gameObject);
    ~MusicComponent();

    void Update(float deltaTime) override;

    void SetMusic(sf::Music* newMusic);
    void SetLoop(bool newLoop);

    void SetVolume(float volume);
    void Play();
    void Stop();
    void Pause();
    void Resume();

   private:
    sf::Music* music = nullptr;
};
}  // namespace MaxrEngine
