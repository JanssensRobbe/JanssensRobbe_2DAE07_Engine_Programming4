#pragma once
#include <iostream>
#include "SpriteComponent.h"
#include "Structs.h"
#include "ButtonManager.h"
#include "../DigDug/DigDugCharacterComponent.h"

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
			if (obj.HasComponent<DigDugCharacterComponent>())
				obj.GetComponent<DigDugCharacterComponent>()->SetDirection(dae::Direction::left);
		}
	};

	class RightCommand : public Command
	{
	public:
		RightCommand() {}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<DigDugCharacterComponent>())
				obj.GetComponent<DigDugCharacterComponent>()->SetDirection(dae::Direction::right);
		}
	};

	class DownCommand : public Command
	{
	public:
		DownCommand(){}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<DigDugCharacterComponent>())
				obj.GetComponent<DigDugCharacterComponent>()->SetDirection(dae::Direction::down);
			else if (obj.HasComponent<ButtonComponent>())
				ButtonManager::GetInstance().SetNextButtonActive();
		}
	};

	class UpCommand : public Command
	{
	public:
		UpCommand() {}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<DigDugCharacterComponent>())
				obj.GetComponent<DigDugCharacterComponent>()->SetDirection(dae::Direction::up);
			else if (obj.HasComponent<ButtonComponent>())
				ButtonManager::GetInstance().SetPreviousButtonActive();
		}
	};

	class PumpCommand : public Command
	{
	public:
		PumpCommand() {}

		virtual void execute(GameObject& obj) override{
			if (obj.HasComponent<DigDugCharacterComponent>())
			{
				obj.GetComponent<DigDugCharacterComponent>()->SetDirection(dae::Direction::none);
				obj.GetComponent<DigDugCharacterComponent>()->SetIsPumping(true);
			}
		}
	};

	class IdleCommand : public Command
	{
	public:
		IdleCommand() {}
		virtual  void execute(GameObject& obj) override {
			if (obj.HasComponent<DigDugCharacterComponent>())
			{
				obj.GetComponent<DigDugCharacterComponent>()->SetDirection(dae::Direction::none);
				obj.GetComponent<DigDugCharacterComponent>()->SetIsPumping(false);
			}

		}
	};

	class ButtonPressedCommand : public Command
	{
	public:
		ButtonPressedCommand() {}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<ButtonComponent>())
				ButtonManager::GetInstance().GetActiveButton().SetSceneLoaded(true);
		}
	};
}

