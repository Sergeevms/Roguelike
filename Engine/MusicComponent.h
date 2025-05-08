#pragma once
#include "Component.h"
#include <SFML/Audio.hpp>
#include "EngineAPI.h"
namespace MaxrEngine
{
	class ENGINE_API MusicComponent :
		public Component
	{
	public:
		MusicComponent(GameObject* gameObject);
		~MusicComponent();

		void Update(float deltaTime) override;
		void Render() override;

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
}

