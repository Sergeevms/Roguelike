#include "pch.h"
#include "MusicComponent.h"

namespace MaxrEngine
{
	MusicComponent::MusicComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	MusicComponent::~MusicComponent()
	{
		music->stop();
	}

	void MusicComponent::Update(float deltaTime)
	{
	}

	void MusicComponent::Render()
	{
	}

	void MusicComponent::SetMusic(sf::Music* newMusic)
	{
		music = newMusic;
	}

	void MusicComponent::SetLoop(bool newLoop)
	{
		music->setLoop(newLoop);
	}

	void MusicComponent::SetVolume(float volume)
	{
		music->setVolume(volume);
	}

	void MusicComponent::Play()
	{
		if (music->getStatus() != sf::Music::Playing)
		{
			music->play();
		}
	}

	void MusicComponent::Stop()
	{
		music->stop();
	}

	void MusicComponent::Pause()
	{
		music->pause();
	}

	void MusicComponent::Resume()
	{
		if (music->getStatus() != sf::Music::Playing)
		{
			music->play();
		}
	}
}