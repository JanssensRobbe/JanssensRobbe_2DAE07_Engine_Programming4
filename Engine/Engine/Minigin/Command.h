#pragma once
#include <iostream>
#include "SpriteComponent.h"
#include "Structs.h"
#include "ButtonManager.h"
#include "../Pengo/PengoCharacterComponent.h"

namespace dae
{
	class Command
	{
	public:
		Command(){}
		virtual void execute(GameObject&) = 0;
	};

	class NullCommand : public Command
	{
	public:
		virtual void execute(GameObject&) override {}
	};

	class LeftCommand : public Command
	{
	public:
		LeftCommand() {}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<PengoCharacterComponent>())
			{
				obj.GetComponent<PengoCharacterComponent>()->SetDirection(dae::Direction::left);
				obj.GetComponent<PengoCharacterComponent>()->SetIsPushing(false);
			}
		}
	};

	class RightCommand : public Command
	{
	public:
		RightCommand() {}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<PengoCharacterComponent>())
			{
				obj.GetComponent<PengoCharacterComponent>()->SetDirection(dae::Direction::right);
				obj.GetComponent<PengoCharacterComponent>()->SetIsPushing(false);
			}
		}
	};

	class DownCommand : public Command
	{
	public:
		DownCommand(){}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<PengoCharacterComponent>())
			{
				obj.GetComponent<PengoCharacterComponent>()->SetDirection(dae::Direction::down);
				obj.GetComponent<PengoCharacterComponent>()->SetIsPushing(false);
			}
			else if (obj.HasComponent<ButtonManager>())
				obj.GetComponent<ButtonManager>()->SetNextButtonActive();
		}
	};

	class UpCommand : public Command
	{
	public:
		UpCommand() {}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<PengoCharacterComponent>())
			{
				obj.GetComponent<PengoCharacterComponent>()->SetDirection(dae::Direction::up);
				obj.GetComponent<PengoCharacterComponent>()->SetIsPushing(false);
			}
			else if (obj.HasComponent<ButtonManager>())
				obj.GetComponent<ButtonManager>()->SetPreviousButtonActive();
		}
	};

	class PushCommand : public Command
	{
	public:
		PushCommand() {}

		virtual void execute(GameObject& obj) override{
			if (obj.HasComponent<PengoCharacterComponent>())
			{
				obj.GetComponent<PengoCharacterComponent>()->SetDirection(dae::Direction::none);
				obj.GetComponent<PengoCharacterComponent>()->SetIsPushing(true);
			}
		}
	};

	class IdleCommand : public Command
	{
	public:
		IdleCommand() {}
		virtual  void execute(GameObject& obj) override {
			if (obj.HasComponent<PengoCharacterComponent>())
			{
				obj.GetComponent<PengoCharacterComponent>()->SetDirection(dae::Direction::none);
				obj.GetComponent<PengoCharacterComponent>()->SetIsPushing(false);
			}

		}
	};

	class ButtonPressedCommand : public Command
	{
	public:
		ButtonPressedCommand() {}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<ButtonComponent>())
				obj.GetComponent<ButtonManager>()->GetActiveButton()->SetSceneLoaded(true);
		}
	};
}

