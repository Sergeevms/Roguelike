#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cassert>
#include "Logger.h"
#include "EngineAPI.h"
#include "Component.h"
#include "TransformComponent.h"

namespace MaxrEngine
{
	class Component;
	class TransformComponent;
	
	class GameObject : public std::enable_shared_from_this<GameObject>
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

		template<typename T, typename... ArgsT>
		std::shared_ptr<T> AddComponent(ArgsT... args)
		{
			if constexpr (!std::is_base_of<Component, T>::value)
			{
				LOG_WARN("T must be derived from Component.");
				return nullptr;
			}

			if constexpr (std::is_same<T, TransformComponent>::value)
			{
				if (GetComponent<TransformComponent>() != nullptr)
				{
					LOG_WARN("Can't add Transform, because it will break the engine loop.");
					return nullptr;
				}
			}			
			std::shared_ptr<T> newComponent = std::make_shared<T>(this, args...);
			components.emplace_back(newComponent);
			std::ostringstream message;
			message << "Added new component: " << std::string(typeid(*newComponent).name()) << " " << newComponent;
			LOG_INFO(message.str());
			return newComponent;
		}

		ENGINE_API void RemoveComponent(Component* component)
		{
			std::ostringstream message;
			message << "Deleting component: " << std::string(typeid(*component).name()) << " " << component;
			LOG_INFO(message.str());
			components.erase(std::remove_if(components.begin(), components.end(),
				[component](std::shared_ptr<Component> obj) {return obj.get() == component; }), components.end());
		}

		ENGINE_API void RemoveComponent(std::weak_ptr<Component> component)
		{
			std::ostringstream message;
			auto componentPtr = component.lock();
			message << "Deleting component: " << std::string(typeid(componentPtr).name()) << " " << componentPtr;
			LOG_INFO(message.str());
			components.erase(std::remove_if(components.begin(), components.end(),
				[componentPtr](std::shared_ptr<Component> obj) {return obj == componentPtr; }), components.end());
		}

		template<typename T>
		T* GetComponent() const
		{
			for (const auto& component : components)
			{
				if (auto casted = std::dynamic_pointer_cast<T>(component))
				{
					return casted.get();
				}
			}
			std::ostringstream message;
			message << typeid(T).name() << " component not found";
			LOG_INFO(message.str());
			return nullptr;
		};

		template<typename T>
		std::shared_ptr<T> GetComponentSharedPtr() const
		{
			for (const auto& component : components)
			{
				if (auto casted = std::dynamic_pointer_cast<T>(component))
				{
					return casted;
				}
			}
			std::ostringstream message;
			message << typeid(T).name() << " component not found";
			LOG_INFO(message.str());
			return std::shared_ptr<T>();
		}

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
			std::ostringstream message;
			message << typeid(T).name() << " component not found";
			LOG_INFO(message.str());
			return nullptr;
		}

		template<typename T>
		std::vector<T*> GetComponents() const
		{
			std::vector<T*> result;
			for (const auto& component : components)
			{
				if (auto casted = std::dynamic_pointer_cast<T>(component))
				{
					result.push_back(casted.get());
				}
			}
			return result;
		}

	private:
		std::vector<std::shared_ptr<Component>> components = {};
		std::string name;
		std::vector<GameObject*> children = {};
	};
}

