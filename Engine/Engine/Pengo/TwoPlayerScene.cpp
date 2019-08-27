#include "pch.h"
#include "TwoPlayerScene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Level.h"
#include "TextComponent.h"
#include "Locator.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "PengoCharacterComponent.h"
#include "AgentComponent.h"
#include "ScoreObserver.h"
#include "SpawnComponent.h"


dae::TwoPlayerScene::TwoPlayerScene(const std::string& name)
	:Scene{name}
{
}

dae::TwoPlayerScene::~TwoPlayerScene()
{
	Locator::UnregisterAll();
}

void dae::TwoPlayerScene::LoadScene()
{
	//AgentComponent::ResetCount();
	CollisionComponent::UnRegister();
	InputManager::GetInstance().ResetActions();
	auto PumpAction = InputAction(0, std::make_shared<PushCommand>(), 'X', -1, WORD(dae::ControllerButton::ButtonA), dae::PlayerOne);
	InputManager::GetInstance().AddAction(PumpAction);
	auto downCommand = InputAction(1, std::make_shared<DownCommand>(), 'S', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(downCommand);
	auto upCommand = InputAction(2, std::make_shared<UpCommand>(), 'W', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(upCommand);
	auto leftCommand = InputAction(3, std::make_shared<LeftCommand>(), 'A', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(leftCommand);
	auto rightCommand = InputAction(4, std::make_shared<RightCommand>(), 'D', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(rightCommand);

	PumpAction = InputAction(5, std::make_shared<PushCommand>(), 'N', -1, WORD(dae::ControllerButton::ButtonA), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(PumpAction);
	downCommand = InputAction(6, std::make_shared<DownCommand>(), 'K', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(downCommand);
	upCommand = InputAction(7, std::make_shared<UpCommand>(), 'I', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(upCommand);
	leftCommand = InputAction(8, std::make_shared<LeftCommand>(), 'J', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(leftCommand);
	rightCommand = InputAction(9, std::make_shared<RightCommand>(), 'L', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerTwo);
	InputManager::GetInstance().AddAction(rightCommand);

	auto subject = new Subject{};
	ScoreObserver* scoreObserver = new ScoreObserver{ subject };
	subject->Attach(scoreObserver);
	Locator::SetSubject(subject);
	auto to = std::make_shared<GameObject>();
	CollisionComponent* CollisionComp = new CollisionComponent{};
	to->AddComponent(CollisionComp);
	Locator::RegisterCollisionComponent(to);

	to = std::make_shared<GameObject>();
	auto level = new LevelComponent("./../Data/PengoLevel2.bin", 2);
	to->AddComponent(level);
	TextComponent* TextComp = new TextComponent{ "Text",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36),{255,255,255} };
	to->AddComponent(TextComp);
	to->SetPosition(0, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	SpawnComponent* spawn = new SpawnComponent{};
	spawn->SpawnPlayer(to, "Character.png", 2, 1, 0.2f, 16.0f, 8, 3.0f, "Lives.png", 0, Point2f{ 0.0f,820.0f }, 3, Point2f{ 384,384 }, dae::SceneType::StartMenu);
	to->AddComponent(spawn);
	Add(to);

	to = std::make_shared<GameObject>();
	spawn = new SpawnComponent{};
	spawn->SpawnPlayer(to, "Character.png", 2, 1, 0.2f, 16.0f, 8, 3.0f, "Lives.png", 1, Point2f{ 350.0f,820.0f }, 3, Point2f{ 288,384 }, dae::SceneType::StartMenu);
	to->AddComponent(spawn);
	Add(to);

	to = std::make_shared<GameObject>();
	TextComponent* TextComp2 = new TextComponent{ "",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36),{255,255,255}, true };
	to->AddComponent(TextComp2);
	to->SetPosition(630, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp6 = new SpriteComponent{ "Enemy.png",2,1,0.2f,16.0f,10,3.0f };
	to->AddComponent(SpriteComp6);
	AgentComponent* agent = new AgentComponent(48, 14, dae::EnemyType::SnoBee);
	Locator::RegisterAgent(AgentComponent::GetCount(), to);
	agent->Initialize();
	to->AddComponent(agent);
	to->SetPosition(192, 192);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp7 = new SpriteComponent{ "Enemy.png",2,1,0.2f,16.0f,10,3.0f };
	to->AddComponent(SpriteComp7);
	AgentComponent* agent2 = new AgentComponent(48, 14, dae::EnemyType::SnoBee);
	Locator::RegisterAgent(AgentComponent::GetCount(), to);
	agent2->Initialize();
	to->AddComponent(agent2);
	to->SetPosition(432, 288);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp8 = new SpriteComponent{ "Enemy.png",2,1,0.2f,16.0f,10,3.0f };
	to->AddComponent(SpriteComp8);
	AgentComponent* agent3 = new AgentComponent(48, 14, dae::EnemyType::SnoBee);
	Locator::RegisterAgent(AgentComponent::GetCount(), to);
	agent3->Initialize();
	to->AddComponent(agent3);
	to->SetPosition(480, 720);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp9 = new SpriteComponent{ "Enemy.png",2,1,0.2f,16.0f,10,3.0f };
	to->AddComponent(SpriteComp9);
	AgentComponent* agent4 = new AgentComponent(48, 14, dae::EnemyType::SnoBee);
	Locator::RegisterAgent(AgentComponent::GetCount(), to);
	agent4->Initialize();
	to->AddComponent(agent4);
	to->SetPosition(192, 432);
	Add(to);

	spawn->SetCount(AgentComponent::GetCount());
	for (auto wall : level->GetWalls())
	{
		if (wall->GetSpawnEggLocation() != Point2f{ 0,0 })
		{
			auto Enemy = std::make_shared<GameObject>();
			SpriteComponent* Sprite = new SpriteComponent{ "Enemy.png",2,1,0.2f,16.0f,10,3.0f };
			Enemy->AddComponent(Sprite);
			AgentComponent* enemyAgent = new AgentComponent(48, 14, dae::EnemyType::SnoBee, true);
			Locator::RegisterAgent(AgentComponent::GetCount(), Enemy);
			enemyAgent->Initialize();
			Enemy->AddComponent(enemyAgent);
			Enemy->SetPosition(wall->GetSpawnEggLocation().x, wall->GetSpawnEggLocation().y);
			Add(Enemy);
		}
	}
	spawn->SetAmount(AgentComponent::GetCount());

	m_IsLoaded = true;
}
