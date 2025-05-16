#pragma once
namespace MaxrEngine
{
	class Scene
	{
		virtual void Start() = 0;
		virtual void Restart() = 0;
		virtual void Stop() = 0;
	};
}

