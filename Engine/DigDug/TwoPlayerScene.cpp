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
	auto PumpAction = Action(0, new PumpCommand{}, 'X', -1, WORD(dae::ControllerButton::ButtonA), dae::PlayerOne);
	InputManager::GetInstance().AddAction(PumpAction);
	auto WalkDownAction = Action(1, new WalkCommand{ dae::Direction::down }, 'S', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(WalkDownAction);
	auto WalkUpAction = Action(2, new WalkCommand{ dae::Direction::up }, 'W', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(WalkUpAction);
	auto WalkLeftAction = Action(3, new WalkCommand{ dae::Direction::left }, 'A', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(WalkLeftAction);
	auto WalkRightAction = Action(4, new WalkCommand{ dae::Direction::right }, 'D', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(WalkRightAction);
	auto PumpAction2 = Action(5, new PumpCommand{}, 'M', -1, WORD(dae::ControllerButton::ButtonA), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(PumpAction);
	auto WalkDownAction2 = Action(6, new WalkCommand{ dae::Direction::down }, 'K', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(WalkDownAction);
	auto WalkUpAction2 = Action(7, new WalkCommand{ dae::Direction::up }, 'I', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(WalkUpAction);
	auto WalkLeftAction2 = Action(8, new WalkCommand{ dae::Direction::left }, 'J', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(WalkLeftAction);
	auto WalkRightAction2 = Action(9, new WalkCommand{ dae::Direction::right }, 'L', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(WalkRightAction);

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
