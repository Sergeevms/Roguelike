#pragma once
namespace MaxrEngine
{
	class ColliderComponent;
	struct Trigger
	{
	public:
		Trigger(ColliderComponent* first, ColliderComponent* second) :
			first(first), second(second) { };
	private:
		ColliderComponent* first;
		ColliderComponent* second;
	};
}

