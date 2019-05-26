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



std::shared_ptr<dae::GameObject>& dae::SpawnComponent::SpawnPlayer(std::shared_ptr<GameObject> obj,std::string SpritePath, int nbCols,int nbRows,float frameSec,float frameSize,int startRow, float scale,
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
	return obj;
}

std::shared_ptr<dae::GameObject>& dae::SpawnComponent::SpawnPooka(std::shared_ptr<GameObject> obj)
{
	// TODO: insert return statement here
	return obj;
}

std::shared_ptr<dae::GameObject>& dae::SpawnComponent::SpawnFygar(std::shared_ptr<GameObject> obj)
{
	// TODO: insert return statement here
	return obj;
}
