#pragma once

namespace MaxrEngine
{
	class AtackComponent;
	class GameObject;

	class AtackSystem
	{
	public:
		ENGINE_API static AtackSystem* Instance();
		ENGINE_API void OneTargetAtack(AtackComponent * atackComponent, GameObject * target);
	private:
		AtackSystem() = default;
		~AtackSystem() = default;
		AtackSystem(const AtackSystem&) = delete;
		AtackSystem& operator=(const AtackSystem&) = delete;
	};
}

