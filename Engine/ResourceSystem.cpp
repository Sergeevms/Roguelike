#include "pch.h"
#include "ResourceSystem.h"

namespace MaxrEngine
{
	ResourceSystem* ResourceSystem::Instance()
	{
		static ResourceSystem resourceSystem;
		return &resourceSystem;
	}

	void ResourceSystem::LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth)
	{
		if (textures.contains(name))
		{
			return;
		}

		sf::Texture* newTexture = new sf::Texture();
		if (newTexture->loadFromFile(sourcePath))
		{
			newTexture->setSmooth(isSmooth);
			textures.emplace(name, newTexture);
		}
		else
		{
			delete newTexture;
		}
	}

	const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
	{
		auto texturePair = textures.find(name);
		if (texturePair != textures.end())
		{
			return texturePair->second;
		}
		else
		{
			return nullptr;
		}
	}

	sf::Texture* ResourceSystem::GetTectureCopy(const std::string& name) const
	{
		auto texturePair = textures.find(name);
		if (texturePair != textures.end())
		{
			return new sf::Texture(*texturePair->second);
		}
		else
		{
			return nullptr;
		}
	}

	void ResourceSystem::DeleteSharedTexture(const std::string& name)
	{
		auto texturePair = textures.find(name);

		sf::Texture* deletingtTexture = texturePair->second;
		textures.erase(texturePair);
		delete deletingtTexture;
	}

	void ResourceSystem::LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
	{
		if (textureMaps.contains(name))
		{
			return;
		}

		sf::Texture textureMap;
		if (textureMap.loadFromFile(sourcePath))
		{
			std::vector<sf::Texture*> textureMapElements;

			auto textureSize = textureMap.getSize();
			int loadedElements = 0;

			for (unsigned y = 0; y <= textureSize.y - elementPixelSize.y; y += elementPixelSize.y)
			{
				if (loadedElements == totalElements)
				{
					break;
				}

				for (unsigned x = 0; x <= textureSize.x - elementPixelSize.x; x += elementPixelSize.x)
				{
					if (loadedElements == totalElements)
					{
						break;
					}

					sf::Texture* newTextureMapElement = new sf::Texture();
					if (newTextureMapElement->loadFromFile(sourcePath, sf::IntRect(x, y, elementPixelSize.x, elementPixelSize.y)))
					{
						newTextureMapElement->setSmooth(isSmooth);
						textureMapElements.push_back(newTextureMapElement);
					}
					else
					{
						delete newTextureMapElement;
					}
					++loadedElements;
				}
			}
			textureMaps.emplace(name, textureMapElements);
		}
	}

	const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end())
		{
			return nullptr;
		}
		else
		{
			return textureMap->second[elementIndex];
		}
	}

	sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end())
		{
			return nullptr;
		}
		else
		{
			return new sf::Texture(*(textureMap->second[elementIndex]));
		}
	}

	int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end())
		{
			return -1;
		}
		else
		{
			return static_cast<int>(textureMap->second.size());
		}
	}

	void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
	{
		auto textureMap = textureMaps.find(name);

		for (auto& texture : textureMap->second)
		{
			delete texture;
		}

		textureMaps.erase(textureMap);
	}

	void ResourceSystem::LoadSound(const std::string& name, std::string sourcePath)
	{
		if (soundBuffers.contains(name))
		{
			return;
		}

		sf::SoundBuffer* buffer = new sf::SoundBuffer();
		if (buffer->loadFromFile(sourcePath))
		{
			soundBuffers.emplace(std::pair<std::string, sf::SoundBuffer*>(name, buffer));
		}
		else
		{
			delete buffer;
		}
	}

	const sf::SoundBuffer* ResourceSystem::GetSoundShared(const std::string& name) const
	{
		auto soundBufferPair = soundBuffers.find(name);
		if (soundBufferPair != soundBuffers.end())
		{
			return soundBufferPair->second;
		}
		else
		{
			return nullptr;
		}
	}

	sf::SoundBuffer* ResourceSystem::GetSoundCopy(const std::string& name) const
	{
		auto soundBufferPair = soundBuffers.find(name);
		if (soundBufferPair != soundBuffers.end())
		{
			sf::SoundBuffer* newBuffer = new sf::SoundBuffer(*soundBufferPair->second);
			return newBuffer;
		}
		else
		{
			return nullptr;
		}
	}

	void ResourceSystem::DeleteSound(const std::string& name)
	{
		auto soundBufferPair = soundBuffers.find(name);
		if (soundBufferPair != soundBuffers.end())
		{
			delete soundBufferPair->second;
			soundBuffers.erase(soundBufferPair);
		}
	}

	void ResourceSystem::LoadMusic(const std::string& name, std::string sourcePath)
	{
		if (musics.contains(name))
		{
			return;
		}

		auto music = new sf::Music();
		if (music->openFromFile(sourcePath))
		{
			musics.emplace(std::pair<std::string, sf::Music*>(name, music));
		}
	}

	const sf::Music* ResourceSystem::GetMusicShared(const std::string& name) const
	{
		auto musicPair = musics.find(name);
		if (musicPair != musics.end())
		{
			return musicPair->second;
		}
		else
		{
			return nullptr;
		}
	}

	void ResourceSystem::DeleteMusic(const std::string& name)
	{
		auto musicPair = musics.find(name);
		if (musicPair != musics.end())
		{
			delete musicPair->second;
			musics.erase(musicPair);
		}
	}

	void ResourceSystem::Clear()
	{
		DeleteAllTextures();
		DeleteAllTextureMaps();
		DeleteAllSounds();
		DeleteAllMusics();
	}

	void ResourceSystem::DeleteAllTextures()
	{
		std::vector<std::string> keysToDelete;
		for (const auto& texturePair : textures)
		{
			keysToDelete.push_back(texturePair.first);
		}
		for (const auto& key : keysToDelete)
		{
			DeleteSharedTexture(key);
		}
	}

	void ResourceSystem::DeleteAllTextureMaps()
	{
		std::vector<std::string> keysToDelete;
		for (const auto& textureMapPair : textureMaps)
		{
			keysToDelete.push_back(textureMapPair.first);
		}
		for (const auto& key : keysToDelete)
		{
			DeleteSharedTextureMap(key);
		}
	}

	void ResourceSystem::DeleteAllSounds()
	{
		std::vector<std::string> keysToDelete;
		for (const auto& soundPair : soundBuffers)
		{
			keysToDelete.push_back(soundPair.first);
		}
		for (const auto& key : keysToDelete)
		{
			DeleteSharedTextureMap(key);
		}
	}

	void ResourceSystem::DeleteAllMusics()
	{
		std::vector<std::string> keysToDelete;
		for (const auto& musicPair : musics)
		{
			keysToDelete.push_back(musicPair.first);
		}
		for (const auto& key : keysToDelete)
		{
			DeleteSharedTextureMap(key);
		}
	}
}