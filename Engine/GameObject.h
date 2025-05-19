#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include "Logger.h"
#include "EngineAPI.h"
#include "Component.h"
#include "TransformComponent.h"

namespace MaxrEngine
{
	class Component;
	class TransformComponent;
	
	class GameObject
	{
	public:
		GameObject();
		GameObject(const std::string& newName);

		~GameObject();

		ENGINE_API std::string GetName() const;
		ENGINE_API void Print(int depth = 0);

		void Update(float deltaTime);
		void Render();

		ENGINE_API void AddChild(GameObject* child);
		ENGINE_API void RemoveChild(GameObject* child);

		template<typename T>
		T* AddComponent()
		{
			if constexpr (!std::is_base_of<Component, T>::value)
			{
				std::cout << "T must be derived from Component." << std::endl;
				return nullptr;
			}

			if constexpr (std::is_same<T, TransformComponent>::value)
			{
				if (GetComponent<TransformComponent>() != nullptr)
				{
					std::cout << "Can't add Transform, because it will break the engine loop." << std::endl;
					return nullptr;
				}
			}
			T* newComponent = new T(this);
			components.push_back(newComponent);
			std::ostringstream message;
			message << "Added new component: " << std::string(typeid(*newComponent).name()) << " " << newComponent;
			LOG_INFO(message.str());
			//std::cout << "Added new component: " << newComponent << std::endl;
			return newComponent;
		}

		ENGINE_API void RemoveComponent(Component* component)
		{
			components.erase(std::remove_if(components.begin(), components.end(),
				[component](Component* obj) {return obj == component; }), components.end());
			delete component;
			std::cout << "Deleted component." << std::endl;
		}

		template<typename T>
		T* GetComponent() const
		{
			for (const auto& component : components)
			{
				if (auto casted = dynamic_cast<T*>(component))
				{
					return casted;
				}
			}
			return nullptr;
		};

		template<typename T>
		T* GetComponentInChildren() const
		{
			T* component = GetComponent<T>();
			if (component || children.size() == 0)
			{
				return component;
			}

			for (const auto& child : children)
			{
				T* childComponent = child->GetComponentInChildren<T>();
				if (childComponent)
				{
					return childComponent;
				}
			}

			return nullptr;
		}

		template<typename T>
		std::vector<T*> GetComponents() const
		{
			std::vector<T*> result;
			for (const auto& component : components)
			{
				if (auto casted = dynamic_cast<T*>(component))
				{
					result.push_back(casted);
				}
			}
			return result;
		}

	private:
		std::vector<Component*> components = {};
		std::string name;
		std::vector<GameObject*> children = {};
	};
}

