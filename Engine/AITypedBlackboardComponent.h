#pragma once
#include "Component.h"
#include <unordered_map>
#include <string>
#include <tuple>
namespace MaxrEngine
{
	template<typename ... ValueTypes>
	class AITypedBlackboardComponent :
		public Component
	{
	public:
		template<typename T>
		using MapType = std::unordered_map<std::string, T>;
		using Data = std::tuple<MapType<ValueTypes>...>;

		AITypedBlackboardComponent(GameObject* gameObject) : Component(gameObject) {};

		virtual void Update(float deltaTime) {};
		virtual void Render() {};

		template<typename T>
		void Set(std::string key, const T& value)
		{
			std::get<MapType<T>>(data)[key] = value;
		}

		template<typename T>
		bool Get(std::string key, T & outValue) const
		{
			auto& map = std::get<MapType<T>>(data);
			auto it = map.find(key);
			if (it == map.end())
			{
				return false;
			}
			else
			{
				outValue = it->second;
				return true;
			}
		}
	protected:
		Data data;
	};
}

