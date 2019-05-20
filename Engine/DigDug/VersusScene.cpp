#include "pch.h"
#include "VersusScene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Level.h"
#include "TextComponent.h"
#include "CharacterComponent.h"

dae::VersusScene::VersusScene(const std::string& name)
	:Scene{name}
{
}


void dae::VersusScene::LoadScene()
{
	InputManager::GetInstance().ResetActions();
	auto PumpAction = Action(0, std::make_shared<PumpCommand>(), 'X', -1, WORD(dae::ControllerButton::ButtonA), dae::PlayerOne);
	InputManager::GetInstance().AddAction(PumpAction);
	auto downCommand = Action(1, std::make_shared<DownCommand>(), 'S', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(downCommand);
	auto upCommand = Action(2, std::make_shared<UpCommand>(), 'W', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(upCommand);
	auto leftCommand = Action(3, std::make_shared<LeftCommand>(), 'A', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(leftCommand);
	auto rightCommand = Action(4, std::make_shared<RightCommand>(), 'D', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(rightCommand);


	auto to = std::make_shared<GameObject>();
	LevelComponent* LevelComp = new LevelComponent();
	to->AddComponent(LevelComp);
	to->SetPosition(0, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	TextComponent* TextComp2 = new TextComponent{ "",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36),{255,255,255}, true };
	to->AddComponent(TextComp2);
	to->SetPosition(630, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp5 = new SpriteComponent{ "DigDug.png",2,1,0.2f,16.0f,8,3.0f };
	to->AddComponent(SpriteComp5);
	CharacterComponent* Character1 = new CharacterComponent{ 0, *SpriteComp5 };
	to->SetPosition(336, 432);
	to->AddComponent(Character1);
	Add(to);
}
