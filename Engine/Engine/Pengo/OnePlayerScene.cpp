#include "pch.h"
#include "OnePlayerScene.h"
#include "Level.h"
#include "TextComponent.h"
#include "PengoCharacterComponent.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Locator.h"
#include "HealthComponent.h"
#include "CollisionComponent.h"
#include "AgentComponent.h"
#include "SpawnComponent.h"
#include "Score.h"
#include "ScoreObserver.h"


dae::OnePlayerScene::OnePlayerScene(const std::string& name)
	:Scene{name}
{
}
dae::OnePlayerScene::~OnePlayerScene()
{
	Locator::UnregisterAll();
} 

void dae::OnePlayerScene::LoadScene()
{
	//AgentComponent::ResetCount();
	CollisionComponent::UnRegister();
	InputManager::GetInstance().ResetActions();
	auto PumpAction = InputAction(0, std::make_shared<PushCommand>(), 'X', -1,WORD(dae::ControllerButton::ButtonA),dae::PlayerOne);
	InputManager::GetInstance().AddAction(PumpAction);
	auto downCommand = InputAction(1, std::make_shared<DownCommand>(), 'S', -1, WORD(dae::ControllerButton::DownArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(downCommand);
	auto upCommand = InputAction(2, std::make_shared<UpCommand>(), 'W', -1, WORD(dae::ControllerButton::UpArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(upCommand);
	auto leftCommand = InputAction(3, std::make_shared<LeftCommand>(), 'A', -1, WORD(dae::ControllerButton::LeftArrow), dae::PlayerOne);
	InputManager::GetInstance().AddAction(leftCommand);
	auto rightCommand = InputAction( 4, std::make_shared<RightCommand>(), 'D', -1, WORD(dae::ControllerButton::RightArrow), dae::PlayerOne);
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
	auto level = new LevelComponent("./../Data/PengoLevel1.bin",1);
	to->AddComponent(level);
	TextComponent* TextComp = new TextComponent{ "Text",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36),{255,255,255} };
	to->AddComponent(TextComp);
	to->SetPosition(0, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	SpawnComponent* spawn = new SpawnComponent{};
	spawn->SpawnPlayer(to, "Character.png", 2, 1, 0.2f, 16.0f, 8, 3.0f, "Lives.png", 0, Point2f{ 0.0f,820.0f }, 3, Point2f{ 336,384 }, dae::SceneType::StartMenu);
	to->AddComponent(spawn);
	Add(to);

	to = std::make_shared<GameObject>();
	TextComponent* TextComp2 = new TextComponent{ "",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36),{255,255,255}, true };
	to->AddComponent(TextComp2);
	to->SetPosition(630, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp6 = new SpriteComponent{ "Enemy.png",2,1,0.2f,16.0f,10,3.0f};
	to->AddComponent(SpriteComp6);
	AgentComponent* agent = new AgentComponent(48, 14, dae::EnemyType::SnoBee);
	Locator::RegisterAgent(AgentComponent::GetCount(),to);
	agent->Initialize();
	to->AddComponent(agent);
	to->SetPosition(192,192);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp7 = new SpriteComponent{ "Enemy.png",2,1,0.2f,16.0f,10,3.0f };
	to->AddComponent(SpriteComp7);
	AgentComponent* agent2 = new AgentComponent(48, 14, dae::EnemyType::SnoBee);
	Locator::RegisterAgent(AgentComponent::GetCount(), to);
	agent2->Initialize();
	to->AddComponent(agent2);
	to->SetPosition(432, 240);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp8 = new SpriteComponent{ "Enemy.png",2,1,0.2f,16.0f,10,3.0f };
	to->AddComponent(SpriteComp8);
	AgentComponent* agent3 = new AgentComponent(48, 14, dae::EnemyType::SnoBee);
	Locator::RegisterAgent(AgentComponent::GetCount(),to);
	agent3->Initialize();
	to->AddComponent(agent3);
	to->SetPosition(432, 768);
	Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp9 = new SpriteComponent{ "Enemy.png",2,1,0.2f,16.0f,10,3.0f };
	to->AddComponent(SpriteComp9);
	AgentComponent* agent4 = new AgentComponent(48, 14, dae::EnemyType::SnoBee);
	Locator::RegisterAgent(AgentComponent::GetCount(), to);
	agent4->Initialize();
	to->AddComponent(agent4);
	to->SetPosition(192, 480);
	Add(to);

	spawn->SetCount(AgentComponent::GetCount());
	for (auto wall : level->GetWalls())
	{
		if (wall->GetSpawnEggLocation() != Point2f{ 0,0 })
		{
			auto Enemy = std::make_shared<GameObject>();
			SpriteComponent* Sprite = new SpriteComponent{ "Enemy.png",2,1,0.2f,16.0f,10,3.0f };
			Enemy->AddComponent(Sprite);
			AgentComponent* enemyAgent = new AgentComponent(48, 14, dae::EnemyType::SnoBee,true);
			Locator::RegisterAgent(AgentComponent::GetCount(), Enemy);
			enemyAgent->Initialize();
			Enemy->AddComponent(enemyAgent);
			Enemy->SetPosition(wall->GetSpawnEggLocation().x,wall->GetSpawnEggLocation().y);
			Add(Enemy);
		}
	}
	spawn->SetAmount(AgentComponent::GetCount());

	m_IsLoaded = true;
}
