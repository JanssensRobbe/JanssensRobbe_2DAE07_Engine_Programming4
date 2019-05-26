#pragma once
namespace dae {
	class GameObject;
	class Action
	{
	public:
		Action() = default;
		virtual ~Action() = default;

		virtual void Invoke(int) = 0;
	};
}

