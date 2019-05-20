#pragma once
#include <iostream>
#include "SpriteComponent.h"
#include "Structs.h"
#include "ButtonManager.h"
#include "CharacterComponent.h"

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
			if (obj.HasComponent<CharacterComponent>())
				obj.GetComponent<CharacterComponent>()->SetDirection(dae::Direction::left);
		}
	};

	class RightCommand : public Command
	{
	public:
		RightCommand() {}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<CharacterComponent>())
				obj.GetComponent<CharacterComponent>()->SetDirection(dae::Direction::right);
		}
	};

	class DownCommand : public Command
	{
	public:
		DownCommand(){}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<CharacterComponent>())
				obj.GetComponent<CharacterComponent>()->SetDirection(dae::Direction::down);
			else if (obj.HasComponent<ButtonComponent>())
				ButtonManager::GetInstance().SetNextButtonActive();
			std::cout << "DownCommand" << std::endl;
		}
	};

	class UpCommand : public Command
	{
	public:
		UpCommand() {}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<CharacterComponent>())
				obj.GetComponent<CharacterComponent>()->SetDirection(dae::Direction::up);
			else if (obj.HasComponent<ButtonComponent>())
				ButtonManager::GetInstance().SetPreviousButtonActive();
			std::cout << "UpCommand" << std::endl;
		}
	};

	class PumpCommand : public Command
	{
	public:
		PumpCommand() {}

		virtual void execute(GameObject& obj) override{
			if (obj.HasComponent<CharacterComponent>())
				obj.GetComponent<CharacterComponent>()->SetDirection(dae::Direction::none);
		}
	};

	class IdleCommand : public Command
	{
	public:
		IdleCommand() {}
		virtual  void execute(GameObject& obj) override {
			if (obj.HasComponent<CharacterComponent>())
				obj.GetComponent<CharacterComponent>()->SetDirection(dae::Direction::none);
		}
	};

	class ButtonPressedCommand : public Command
	{
	public:
		ButtonPressedCommand() {}
		virtual void execute(GameObject& obj) override {
			if (obj.HasComponent<ButtonComponent>())
				ButtonManager::GetInstance().GetActiveButton().SetSceneLoaded(true);
			std::cout << "ButtonPressedCommand" << std::endl;
		}
	};
}

