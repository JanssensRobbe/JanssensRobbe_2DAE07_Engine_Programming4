#include "pch.h"
#include "OnePlayerScene.h"
#include "Level.h"
#include "TextComponent.h"
#include "DigDugCharacterComponent.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Locator.h"
#include "AgentComponent.h"
#include "HealthComponent.h"
#include "CollisionComponent.h"
#include "SpawnComponent.h"
#include "Score.h"


dae::OnePlayerScene::OnePlayerScene(const std::string& name)
	:Scene{name}
{

}
dae::OnePlayerScene::~OnePlayerScene()
{

}

void dae::OnePlayerScene::LoadScene()
{
	InputManager::GetInstance().ResetActions();
	auto PumpAction = InputAction(0, std::make_shared<PumpCommand>(), 'X', -1,WORD(dae::ControllerButton::ButtonA),dae::PlayerOne);
	InputManager::GetInstance().AddAction(PumpAction);
	auto downCommand = InputAction(1, std::make_shared<DownCommand>(), 'S', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(downCommand);
	auto upCommand = InputAction(2, std::make_shared<UpCommand>(), 'W', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(upCommand);
	auto leftCommand = InputAction(3, std::make_shared<LeftCommand>(), 'A', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(leftCommand);
	auto rightCommand = InputAction( 4, std::make_shared<RightCommand>(), 'D', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(rightCommand);

	Score::GetInstance().Init();
	auto to = std::make_shared<GameObject>();
	LevelComponent* LevelComp = new LevelComponent("./../Data/Level1.bin",1);
	to->AddComponent(LevelComp);
	to->SetPosition(0, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	CollisionComponent* CollisionComp = new CollisionComponent{};
	to->AddComponent(CollisionComp);
	Locator::RegisterCollisionComponent(to);


	auto spawn = std::make_shared<SpawnComponent>();
	to = std::make_shared<GameObject>();
	spawn->SpawnPlayer(to, "DigDug.png", 2, 1, 0.2f, 16.0f, 8, 3.0f, "Lives.png", 0, Point2f{ 0.0f,820.0f }, 3, Point2f{ 336,432 }, dae::SceneType::StartMenu);
	Add(to);
	to = std::make_shared<GameObject>();

	to = std::make_shared<GameObject>();
	TextComponent* TextComp2 = new TextComponent{ "",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36),{255,255,255}, true };
	to->AddComponent(TextComp2);
	to->SetPosition(630, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp6 = new SpriteComponent{ "Enemies.png",2,1,0.2f,16.0f,0,3.0f};
	to->AddComponent(SpriteComp6);
	AgentComponent* agent = new AgentComponent(4, 48, 14, dae::EnemyType::Pooka);
	agent->Initialize();
	Locator::RegisterAgent(0,to);
	to->AddComponent(agent);
	to->SetPosition(192,192);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp7 = new SpriteComponent{ "Enemies.png",2,1,0.2f,16.0f,8,3.0f };
	to->AddComponent(SpriteComp7);
	AgentComponent* agent2 = new AgentComponent(4, 48, 14, dae::EnemyType::Fygar);
	agent2->Initialize();
	Locator::RegisterAgent(1, to);
	to->AddComponent(agent2);
	to->SetPosition(480, 192);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp8 = new SpriteComponent{ "Enemies.png",2,1,0.2f,16.0f,0,3.0f };
	to->AddComponent(SpriteComp8);
	AgentComponent* agent3 = new AgentComponent(4, 48, 14, dae::EnemyType::Pooka);
	agent3->Initialize();
	Locator::RegisterAgent(2, to);
	to->AddComponent(agent3);
	to->SetPosition(480, 720);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp9 = new SpriteComponent{ "Enemies.png",2,1,0.2f,16.0f,0,3.0f };
	to->AddComponent(SpriteComp9);
	AgentComponent* agent4 = new AgentComponent(4, 48, 14, dae::EnemyType::Pooka);
	agent4->Initialize();
	Locator::RegisterAgent(3, to);
	to->AddComponent(agent4);
	to->SetPosition(192, 720);
	Add(to);
}

