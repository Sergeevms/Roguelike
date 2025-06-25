#pragma once
#include "EngineAPI.h"
namespace MaxrEngine
{
	class IFixedUpdateSytem
	{
	public:
		ENGINE_API IFixedUpdateSytem();
		ENGINE_API virtual ~IFixedUpdateSytem();
		ENGINE_API float GetFixedUpdateTime() const;
		ENGINE_API void SetFixedUpdateTime(const float newFixedUpdateTime);
		ENGINE_API virtual void Update() = 0;
	protected:
		float fixedUpdateTime = 0.015f;
	};
}

