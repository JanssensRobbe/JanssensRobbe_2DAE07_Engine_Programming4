#pragma once
namespace dae {
	class GameObject;
	class Condition
	{
	public:
		Condition() = default;
		virtual ~Condition() = default;

		virtual bool IsTriggered(int) = 0;
	};
}