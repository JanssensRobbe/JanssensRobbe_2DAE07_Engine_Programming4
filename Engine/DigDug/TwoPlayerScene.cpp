#include "pch.h"
#include "TwoPlayerScene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Level.h"
#include "TextComponent.h"
#include "ServiceLocator.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "DigDugCharacterComponent.h"
#include "AgentComponent.h"
#include "SpawnComponent.h"


dae::TwoPlayerScene::TwoPlayerScene(const std::string& name)
	:Scene{name}
{

}



void dae::TwoPlayerScene::LoadScene()
{
	InputManager::GetInstance().ResetActions();
	auto PumpAction = InputAction(0,std::make_shared<PumpCommand>(), 'X', -1, WORD(dae::ControllerButton::ButtonA), dae::PlayerOne);
	InputManager::GetInstance().AddAction(PumpAction);
	auto downCommand = InputAction(1, std::make_shared<DownCommand>(), 'S', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(downCommand);
	auto upCommand = InputAction(2, std::make_shared<UpCommand>(), 'W', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(upCommand);
	auto leftCommand = InputAction(3, std::make_shared<LeftCommand>(), 'A', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(leftCommand);
	auto rightCommand = InputAction(4, std::make_shared<RightCommand>(), 'D', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(rightCommand);
	auto PumpAction2 = InputAction(5, std::make_shared<PumpCommand>(), 'H', -1, WORD(dae::ControllerButton::ButtonA), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(PumpAction2);
	auto downCommand2 = InputAction(6, std::make_shared<DownCommand>(), 'K', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(downCommand2);
	auto upCommand2 = InputAction(7, std::make_shared<UpCommand>(), 'I', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(upCommand2);
	auto leftCommand2 = InputAction(8, std::make_shared<LeftCommand>(), 'J', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(leftCommand2);
	auto rightCommand2 = InputAction(9, std::make_shared<RightCommand>(), 'L', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(rightCommand2);



	auto to = std::make_shared<GameObject>();
	LevelComponent* LevelComp = new LevelComponent("./../data/Level1.bin",2);
	to->AddComponent(LevelComp);
	to->SetPosition(0, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	CollisionComponent* CollisionComp = new CollisionComponent{};
	to->AddComponent(CollisionComp);
	ServiceLocator::RegisterCollisionComponent(to);


	auto spawn = std::make_shared<SpawnComponent>();
	to = std::make_shared<GameObject>();
	Add(spawn->SpawnPlayer(to, "DigDug.png", 2, 1, 0.2f, 16.0f, 8, 3.0f, "Lives.png", 0, Point2f{ 0.0f,820.0f }, 3, Point2f{ 336,432 }, dae::SceneType::WinnerMenu));


	spawn = std::make_shared<SpawnComponent>();
	to = std::make_shared<GameObject>();
	Add(spawn->SpawnPlayer(to, "DigDug.png", 2, 1, 0.2f, 16.0f, 8, 3.0f, "Lives.png", 1, Point2f{ 500.0f, 820.0f }, 3, Point2f{ 436,432 }, dae::SceneType::WinnerMenu));

	to = std::make_shared<GameObject>();
	TextComponent* TextComp2 = new TextComponent{ "",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36),{255,255,255}, true };
	to->AddComponent(TextComp2);
	to->SetPosition(630, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp12 = new SpriteComponent{ "Enemies.png",2,1,0.2f,16.0f,0,3.0f };
	to->AddComponent(SpriteComp12);
	AgentComponent* agent = new AgentComponent(4, 48, 14,EnemyType::Pooka);
	agent->Initialize();
	ServiceLocator::RegisterAgent(0, to);
	to->AddComponent(agent);
	to->SetPosition(240, 432);
	Add(to);
}
