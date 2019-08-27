#include "pch.h"
#include "SpawnComponent.h"
#include "SpriteComponent.h"
#include "Locator.h"
#include "AgentComponent.h"
#include "HealthComponent.h"
#include "PengoCharacterComponent.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "AgentComponent.h"


dae::SpawnComponent::SpawnComponent()
{
	m_pTexture = new TextureComponent{ "SpawnBall.png" };
}


void dae::SpawnComponent::Update(float deltaTime)
{
	if (m_IsSpawning)
	{
		m_EnemySpawnTimer += deltaTime;

		if (m_EnemySpawnTimer >= m_EnemySpawnCooldown)
		{
			m_EnemySpawnTimer = 0.0f;
			if (unsigned int(m_Count) < Locator::GetAgents().size())
			{
				Locator::GetAgent(m_Count)->GetComponent<AgentComponent>()->SetInvisible(false);
				auto playerPos = Locator::GetAgent(m_Count)->GetComponent<AgentComponent>()->GetTransform()->GetPosition();
				auto locationIndex = int(playerPos.x) / 48 + int(playerPos.y) / 48 * 14;
				Locator::GetWall(locationIndex)->DeleteWall();
				Locator::GetAgent(m_Count)->GetComponent<SpriteComponent>()->SetActive(true);
				++m_Count;
				--m_Amount;
			}
			else
				m_IsSpawning = false;
		}
	}
}

void dae::SpawnComponent::Render()
{
	for (int i{}; i < m_Amount; ++i)
	{
		m_pTexture->Render(Rectf{ i * 16.0f,32.0f,16.0f,16.0f }, Rectf{ 0.0f,0.0f,8.0f,8.0f });
	}
}

void dae::SpawnComponent::SpawnPlayer(std::shared_ptr<GameObject>& obj,std::string SpritePath, int nbCols,int nbRows,float frameSec,float frameSize,int startRow, float scale,
	std::string HealthTexturePath, int playerindex, Point2f healthPosition, int health,
	Point2f position, SceneType endscreenType)
{
	obj = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp = new SpriteComponent{ SpritePath,nbCols,nbRows,frameSec,frameSize,startRow,scale };
	obj->AddComponent(SpriteComp);
	HealthComponent* healthComponent = new HealthComponent{ HealthTexturePath,playerindex,healthPosition,health };
	obj->AddComponent(healthComponent);
	CharacterComponent* Character = new PengoCharacterComponent{ (DWORD)playerindex, *SpriteComp,position, endscreenType };
	obj->SetPosition(position.x,position.y);
	obj->AddComponent(Character);
	Locator::RegisterPlayer(playerindex,obj);
	SceneManager::GetInstance().AddCharacter(*Character);

}

void dae::SpawnComponent::SpawnSnobee(std::shared_ptr<GameObject>& obj,std::string EnemiesPath,int nrRows,int nrCols, float frameSec, float frameSize, float scale
	,int gridSize,int agentIndex,int NbColsMap,Point2f pos)
{
	obj = std::make_shared<GameObject>();
	 SpriteComponent* SpriteComp = new SpriteComponent{ EnemiesPath,nrRows,nrCols,frameSec,frameSize,0,scale };
	 obj->AddComponent(SpriteComp);
	 AgentComponent* agent = new AgentComponent(gridSize, NbColsMap, dae::EnemyType::SnoBee);
	 agent->Initialize();
	 Locator::RegisterAgent(agentIndex,obj);
	 obj->AddComponent(agent);
	 obj->SetPosition(pos.x, pos.y);
}
