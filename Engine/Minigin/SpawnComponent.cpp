#include "MiniginPCH.h"
#include "SpawnComponent.h"
#include "SpriteComponent.h"
#include "ServiceLocator.h"
#include "./../DigDug/AgentComponent.h"
#include "./../DigDug/HealthComponent.h"
#include "./../DigDug/DigDugCharacterComponent.h"


dae::SpawnComponent::SpawnComponent()
{
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
	CharacterComponent* Character = new DigDugCharacterComponent{ (DWORD)playerindex, *SpriteComp,position, endscreenType };
	obj->SetPosition(position.x,position.y);
	obj->AddComponent(Character);
	ServiceLocator::RegisterPlayer(playerindex, obj);
	SceneManager::GetInstance().AddCharacter(*Character);

}

void dae::SpawnComponent::SpawnPooka(std::shared_ptr<GameObject>& obj,std::string EnemiesPath,int nrRows,int nrCols, float frameSec, float frameSize, float scale, 
	int MaxNrInflate,int gridSize,int NbColsMap, int agentIndex,Point2f pos)
{
	obj = std::make_shared<GameObject>();
	 SpriteComponent* SpriteComp = new SpriteComponent{ EnemiesPath,nrRows,nrCols,frameSec,frameSize,0,scale };
	 obj->AddComponent(SpriteComp);
	 AgentComponent* agent = new AgentComponent(MaxNrInflate, gridSize, NbColsMap, dae::EnemyType::Fygar);
	 agent->Initialize();
	 ServiceLocator::RegisterAgent(agentIndex, obj);
	 obj->AddComponent(agent);
	 obj->SetPosition(pos.x, pos.y);
}

void dae::SpawnComponent::SpawnFygar(std::shared_ptr<GameObject>& obj, std::string EnemiesPath, int nrRows, int nrCols, float frameSec, float frameSize, float scale,
	int MaxNrInflate, int gridSize, int NbColsMap, int agentIndex, Point2f pos)
{
	obj = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp = new SpriteComponent{ EnemiesPath,nrRows,nrCols,frameSec,frameSize,8,scale };
	obj->AddComponent(SpriteComp);
	AgentComponent* agent = new AgentComponent(MaxNrInflate, gridSize, NbColsMap, dae::EnemyType::Pooka);
	agent->Initialize();
	ServiceLocator::RegisterAgent(agentIndex, obj);
	obj->AddComponent(agent);
	obj->SetPosition(pos.x, pos.y);
}
