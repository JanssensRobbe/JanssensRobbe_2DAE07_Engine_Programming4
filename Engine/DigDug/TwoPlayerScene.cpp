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
	spawn->SpawnPlayer(to, "DigDug.png", 2, 1, 0.2f, 16.0f, 8, 3.0f, "Lives.png", 0, Point2f{ 0.0f,820.0f }, 3, Point2f{ 336,432 }, dae::SceneType::StartMenu);
	Add(to);


	spawn = std::make_shared<SpawnComponent>();
	to = std::make_shared<GameObject>();
	spawn->SpawnPlayer(to, "DigDug.png", 2, 1, 0.2f, 16.0f, 8, 3.0f, "Lives.png", 1, Point2f{ 500.0f, 820.0f }, 3, Point2f{ 436,432 }, dae::SceneType::StartMenu);
	Add(to);

	to = std::make_shared<GameObject>();
	TextComponent* TextComp2 = new TextComponent{ "",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36),{255,255,255}, true };
	to->AddComponent(TextComp2);
	to->SetPosition(630, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp6 = new SpriteComponent{ "Enemies.png",2,1,0.2f,16.0f,0,3.0f };
	to->AddComponent(SpriteComp6);
	AgentComponent* agent = new AgentComponent(4, 48, 14, dae::EnemyType::Pooka);
	agent->Initialize();
	ServiceLocator::RegisterAgent(0, to);
	to->AddComponent(agent);
	to->SetPosition(192, 192);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp7 = new SpriteComponent{ "Enemies.png",2,1,0.2f,16.0f,8,3.0f };
	to->AddComponent(SpriteComp7);
	AgentComponent* agent2 = new AgentComponent(4, 48, 14, dae::EnemyType::Fygar);
	agent2->Initialize();
	ServiceLocator::RegisterAgent(1, to);
	to->AddComponent(agent2);
	to->SetPosition(480, 192);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp8 = new SpriteComponent{ "Enemies.png",2,1,0.2f,16.0f,0,3.0f };
	to->AddComponent(SpriteComp8);
	AgentComponent* agent3 = new AgentComponent(4, 48, 14, dae::EnemyType::Pooka);
	agent3->Initialize();
	ServiceLocator::RegisterAgent(2, to);
	to->AddComponent(agent3);
	to->SetPosition(480, 720);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp9 = new SpriteComponent{ "Enemies.png",2,1,0.2f,16.0f,0,3.0f };
	to->AddComponent(SpriteComp9);
	AgentComponent* agent4 = new AgentComponent(4, 48, 14, dae::EnemyType::Pooka);
	agent4->Initialize();
	ServiceLocator::RegisterAgent(3, to);
	to->AddComponent(agent4);
	to->SetPosition(192, 720);
	Add(to);
}
