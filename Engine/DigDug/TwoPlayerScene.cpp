#include "pch.h"
#include "TwoPlayerScene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Level.h"
#include "TextComponent.h"
#include "CharacterComponent.h"


dae::TwoPlayerScene::TwoPlayerScene(const std::string& name)
	:Scene{name}
{

}



void dae::TwoPlayerScene::LoadScene()
{
	InputManager::GetInstance().ResetActions();
	auto PumpAction = Action(0,std::make_shared<PumpCommand>(), 'X', -1, WORD(dae::ControllerButton::ButtonA), dae::PlayerOne);
	InputManager::GetInstance().AddAction(PumpAction);
	auto downCommand = Action(1, std::make_shared<DownCommand>(), 'S', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(downCommand);
	auto upCommand = Action(2, std::make_shared<UpCommand>(), 'W', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(upCommand);
	auto leftCommand = Action(3, std::make_shared<LeftCommand>(), 'A', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(leftCommand);
	auto rightCommand = Action(4, std::make_shared<RightCommand>(), 'D', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(rightCommand);
	auto PumpAction2 = Action(5, std::make_shared<PumpCommand>(), 'M', -1, WORD(dae::ControllerButton::ButtonA), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(PumpAction);
	auto downCommand2 = Action(6, std::make_shared<DownCommand>(), 'K', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(downCommand2);
	auto upCommand2 = Action(7, std::make_shared<UpCommand>(), 'I', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(upCommand2);
	auto leftCommand2 = Action(8, std::make_shared<LeftCommand>(), 'J', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(leftCommand2);
	auto rightCommand2 = Action(9, std::make_shared<RightCommand>(), 'L', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(rightCommand2);

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

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp6 = new SpriteComponent{ "DigDug.png",2,1,0.2f,16.0f,8,3.0f };
	to->AddComponent(SpriteComp6);
	CharacterComponent* Character2 = new CharacterComponent{ 1, *SpriteComp6 };
	to->SetPosition(436, 432);
	to->AddComponent(Character2);
	Add(to);
}
