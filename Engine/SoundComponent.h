#pragma once
#include "Component.h"
#include "SFML/Audio.hpp"

namespace MaxrEngine
{
	class SoundComponent : 
		public Component
	{
	public:
		SoundComponent(GameObject* gameObject);
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
}

