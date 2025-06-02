#pragma once
namespace MaxrEngine
{
	class IFixedUpdateSytem
	{
	public:
		IFixedUpdateSytem();
		virtual ~IFixedUpdateSytem();
		float GetFixedUpdateTime() const;
		void SetFixedUpdateTime(const float newFixedUpdateTime);
		virtual void Update() = 0;
	protected:
		float fixedUpdateTime = 0.015f;
	};
}

