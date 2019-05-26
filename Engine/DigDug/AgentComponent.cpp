#include "pch.h"
#include "AgentComponent.h"
#include "State.h"
#include "Transition.h"
#include "Level.h"
#include "Structs.h"
#include "Actions.h"
#include "Conditions.h"
#include "DigDugCharacterComponent.h"
#include "ServiceLocator.h"
#include "SpriteComponent.h"
#include "Score.h"
#include<math.h>



int dae::AgentComponent::m_Count = 0;

dae::AgentComponent::AgentComponent(int maxNumberInflate, int gridSize, int nbColumns, dae::EnemyType enemyType)
	:m_MaxInflate(maxNumberInflate)
	,m_GridSize{ gridSize }
	,m_NumberOfColumns{nbColumns}
	,m_EnemyType{enemyType}
	, m_pShootTexture{ new TextureComponent{"FireRight.png"} }
	, m_pScore(std::make_shared<Score>())
{
	auto boundries = SceneManager::GetInstance().GetBoundries();
	m_XLimits.x = boundries.left;
	m_XLimits.y = boundries.left + boundries.width - 48.0f;
	m_YLimits.x = boundries.bottom;
	m_YLimits.y = boundries.bottom + boundries.height;
}

dae::AgentComponent::~AgentComponent()
{
	delete m_pStateMachine;
	delete m_pShootTexture;
}

void dae::AgentComponent::Update(float deltaTime)
{
	if(m_Direction == Direction::right || m_Direction == Direction::down)
		m_TileIndex = int(int(GetTransform()->GetPosition().x)/48 ) + int(int(GetTransform()->GetPosition().y) / 48)*14;
	else
		m_TileIndex = int(int(GetTransform()->GetPosition().x + 47) / 48) + int(int(GetTransform()->GetPosition().y + 47) / 48) * 14;

	if (!m_IsRegistered)
	{
		m_CollsionIndex = ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->AddCollider(Tag{ "Enemy" }, Rectf{ GetTransform()->GetPosition().x, GetTransform()->GetPosition().y, 48.0f,48.0f });
		m_IsRegistered = true;
	}
	else if (!m_IsDead && !m_IsShooting)
		ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollsionIndex, Rectf{ GetTransform()->GetPosition().x, GetTransform()->GetPosition().y, 48.0f,48.0f });
	else if (!m_IsDead && m_IsShooting && m_Direction == Direction::right)
	{
		ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollsionIndex, Rectf{ GetTransform()->GetPosition().x + 48.0f, GetTransform()->GetPosition().y, 96.0f,48.0f });
	}
	else if (!m_IsDead && m_IsShooting && m_Direction == Direction::left)
	{
		ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollsionIndex, Rectf{ GetTransform()->GetPosition().x - 96.0f, GetTransform()->GetPosition().y, 96.0f,48.0f });
	}
	m_ElapsedTime = deltaTime;
	if (!m_Init)
		return;
	if (m_IsIdle)
	{
		if (m_InitIdleTime > 0.0f)
			m_InitIdleTime -= deltaTime;
		else if (GetClosestPlayerDistance() < 200.0f)
			m_IsIdle = false;
	}
	if (m_IsActive)
		m_pStateMachine->Update(deltaTime);

	Collision();
	RockCollision();
}

void dae::AgentComponent::Render()
{
	if (m_IsShooting && m_EnemyType == EnemyType::Fygar  && m_Direction == Direction::right)
	{
		m_pShootTexture->SetTexture("FireRight.png");
		m_pShootTexture->Render(Rectf{ GetTransform()->GetPosition().x + 48.0f, GetTransform()->GetPosition().y, 96.0f,48.0f }, Rectf{ 0.0f,0.0f,48.0f,16.0f });
	}
	else if (m_IsShooting && m_EnemyType == EnemyType::Fygar && m_Direction == Direction::left)
	{
			m_pShootTexture->SetTexture("FireLeft.png");
			m_pShootTexture->Render(Rectf{ GetTransform()->GetPosition().x - 96.0f, GetTransform()->GetPosition().y, 96.0f,48.0f }, Rectf{ 0.0f,0.0f,48.0f,16.0f });
	}
}

void dae::AgentComponent::Initialize()
{
	m_pScore->Init();
	//TODO fix animation going right
	State* run = new State{};
	State* changeToInvis = new State{};
	State* changeToNormal = new State{};
	State* inflate = new State{};
	State* dead = new State{};
	State* hitByRock = new State{};
	State* idle = new State{};

	idle->SetTransition(std::make_shared<Transition>(std::make_shared<StopBeingIdle>(), run));
	idle->SetTransition(std::make_shared<Transition>( std::make_shared<IsHitByRock>(), hitByRock));


	inflate->SetAction(std::make_shared<InflateAction>(),dae::ActionName::Action);
	inflate->SetTransition(std::make_shared<Transition>( std::make_shared<IsDead>() , dead));

	dead->SetAction(std::make_shared<DisableCollisionAction>(), dae::ActionName::EntryAction);
	dead->SetAction(std::make_shared<DeadAction>(), dae::ActionName::Action);

	hitByRock->SetAction(std::make_shared<DisableCollisionAction>(), dae::ActionName::EntryAction);
	hitByRock->SetAction(std::make_shared<DeadAction>(), dae::ActionName::Action);

	run->SetAction(std::make_shared<WalkAction>(), dae::ActionName::Action);
	run->SetTransition(std::make_shared<Transition>(std::make_shared<StartGoingInvisible>() , changeToInvis));
	run->SetTransition(std::make_shared<Transition>(std::make_shared<StopGoingInvisible>() , changeToNormal));
	run->SetTransition(std::make_shared<Transition>(std::make_shared<StartBeingInflated>() , inflate));
	run->SetTransition(std::make_shared<Transition>(std::make_shared<IsHitByRock>() , hitByRock));

	m_pStateMachine = new StateMachine(std::vector<State*>{run, changeToInvis, changeToNormal, inflate, dead, hitByRock, idle}, idle, m_Count);
	m_thisInstance = m_Count;
	++m_Count;
	m_Init = true;
}

void dae::AgentComponent::Walk()
{
	auto pos = GetTransform()->GetPosition();
	switch (m_Direction)
	{
	case dae::Direction::right:
		if ((ServiceLocator::GetTile(m_TileIndex + 1)->tileName == TileName::Black || ServiceLocator::GetTile(m_TileIndex + 1)->tileName == TileName::Sky)
			&& pos.x < m_XLimits.y )
			GetTransform()->SetPosition(pos.x + m_MovementSpeed * m_ElapsedTime, pos.y);
		else if (ServiceLocator::GetTile(m_TileIndex - 14)->tileName == TileName::Black )
			m_Direction = Direction::up;
		else if (ServiceLocator::GetTile(m_TileIndex + 14)->tileName == TileName::Black)
			m_Direction = Direction::down;
		else
			m_Direction = Direction::left;
		break;
	case dae::Direction::down:
		if ((ServiceLocator::GetTile(m_TileIndex + 14)->tileName == TileName::Black || ServiceLocator::GetTile(m_TileIndex + 14)->tileName == TileName::Sky)
			&& pos.y < m_YLimits.y)
			GetTransform()->SetPosition(pos.x, pos.y + m_MovementSpeed * m_ElapsedTime);
		else if (ServiceLocator::GetTile(m_TileIndex - 1)->tileName == TileName::Black || ServiceLocator::GetTile(m_TileIndex - 1)->tileName == TileName::Sky)
			m_Direction = Direction::left;
		else if (ServiceLocator::GetTile(m_TileIndex + 1)->tileName == TileName::Black || ServiceLocator::GetTile(m_TileIndex + 1)->tileName == TileName::Sky)
			m_Direction = Direction::right;
		else
			m_Direction = Direction::up;
		break;
	case dae::Direction::left:
		if ((ServiceLocator::GetTile(m_TileIndex - 1)->tileName == TileName::Black || ServiceLocator::GetTile(m_TileIndex - 1)->tileName == TileName::Sky)
			&& pos.x > m_XLimits.x)
			GetTransform()->SetPosition(pos.x - m_MovementSpeed * m_ElapsedTime, pos.y);
		else if (ServiceLocator::GetTile(m_TileIndex - 14)->tileName == TileName::Black )
			m_Direction = Direction::up;
		else if (ServiceLocator::GetTile(m_TileIndex + 14)->tileName == TileName::Black)
			m_Direction = Direction::down;
		else
			m_Direction = Direction::right;
		break;
	case dae::Direction::up:
		if (ServiceLocator::GetTile(m_TileIndex - 14)->tileName == TileName::Black
			&& pos.y > m_YLimits.x)
			GetTransform()->SetPosition(pos.x, pos.y - m_MovementSpeed * m_ElapsedTime);
		else if (ServiceLocator::GetTile(m_TileIndex  - 1)->tileName == TileName::Black || ServiceLocator::GetTile(m_TileIndex - 1)->tileName == TileName::Sky)
			m_Direction = Direction::left;
		else if (ServiceLocator::GetTile(m_TileIndex + 1)->tileName == TileName::Black || ServiceLocator::GetTile(m_TileIndex + 1)->tileName == TileName::Sky)
			m_Direction = Direction::right;
		else
			m_Direction = Direction::down;
		break;
	}

	UNREFERENCED_PARAMETER(pos);
	if (GetGameObject()->HasComponent<SpriteComponent>())
	{
		if (m_EnemyType == EnemyType::Pooka)
			GetGameObject()->GetComponent<SpriteComponent>()->SetRow(0);
		else
			GetGameObject()->GetComponent<SpriteComponent>()->SetRow(8);
	}
	if (m_EnemyType == EnemyType::Fygar && m_ShootCurrentTime < m_ShootCoolDown  && !m_IsShooting)
	{
		m_ShootCurrentTime += m_ElapsedTime;
	}
	else if (m_EnemyType == EnemyType::Fygar && m_ShootCurrentTime >= m_ShootCoolDown && !m_IsShooting && (m_Direction == Direction::right || m_Direction == Direction::left))
	{
		m_IsShooting = true;
		m_ShootCurrentTime = 0.0f;
	}
	else if (m_EnemyType == EnemyType::Fygar && m_IsShooting)
	{
		if (m_ShootDuration > 0.0f)
			m_ShootDuration -= m_ElapsedTime;
		else
		{
			m_ShootDuration = 1.0f;
			m_IsShooting = false;
		}
	}
}

int dae::AgentComponent::calculateIndex() const
{
	const int x = static_cast<const int>(GetTransform()->GetPosition().x) / m_GridSize;
	const int y = static_cast<const int>(GetTransform()->GetPosition().y) / m_GridSize;
	return y * m_NumberOfColumns + x;
}

int dae::AgentComponent::GetClosestPlayerTileIndex() const
{
	auto& players = ServiceLocator::GetPlayers();
	int closestIndex = -1;
	float closestDistance = -1.0f;
	for (const auto player : players)
	{
		if (closestIndex == -1)
			closestIndex = player.first;
		Point2f pPosition{player.second->GetTransform()->GetPosition()};
		const float dist = (float)pow((float)pow(pPosition.x - GetTransform()->GetPosition().x,2 ) + (float)pow(pPosition.y - GetTransform()->GetPosition().y,2),0.5);
		if (closestDistance == -1)
			closestDistance = dist;
		else if (dist < closestDistance)
		{
			closestDistance = dist;
			closestIndex = player.first;
		}
	}
	if (closestIndex != -1)
	{
		const int x = static_cast<int>(players[closestIndex]->GetTransform()->GetPosition().x) / m_GridSize;
		const int y = static_cast<int>(players[closestIndex]->GetTransform()->GetPosition().y) / m_GridSize;
		return y * m_NumberOfColumns + x;
	}
	return -1;
}

int dae::AgentComponent::GetClosestPlayerIndex() const
{
	auto& players = ServiceLocator::GetPlayers();
	int closestIndex = -1;
	float closestDistance = -1.0f;
	for (const auto player : players)
	{
		if (closestIndex == -1)
			closestIndex = player.first;
		Point2f pPosition{ player.second->GetTransform()->GetPosition() };
		const float dist = (float)pow((float)pow(pPosition.x - GetTransform()->GetPosition().x, 2) + (float)pow(pPosition.y - GetTransform()->GetPosition().y, 2), 0.5);
		if (closestDistance == -1)
			closestDistance = dist;
		else if (dist < closestDistance)
		{
			closestDistance = dist;
			closestIndex = player.first;
		}
	}
	return closestIndex;
}

float dae::AgentComponent::GetClosestPlayerDistance() const
{
	auto& players = ServiceLocator::GetPlayers();
	float closestDist = -1.0f;
	for (const auto player : players)
	{
		//if (player.second->GetComponent<DigDugCharacterComponent>()->GetIsDead())
			//continue;
		const Point2f pPosition = player.second->GetTransform()->GetPosition();
		const float dist = (float)pow((float)pow(pPosition.x - GetTransform()->GetPosition().x, 2) + (float)pow(pPosition.y - GetTransform()->GetPosition().y, 2), 0.5);
		if (closestDist < 0.0f)
			closestDist = dist;
		else if (dist < closestDist)
			closestDist = dist;
	}
	return closestDist;
}

void dae::AgentComponent::Collision()
{
	if (!m_IsInvis)
	{
		bool isHit = ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "PlayerArrow" },
			Rectf{ GetTransform()->GetPosition().x, GetTransform()->GetPosition().y,48.0f,48.0f });
		
		if (isHit && m_CurrentInflateTime <= 0.0f)
		{
			m_CurrentInflateTime = 0.4f;
			m_IsBeingInflated = true;
			m_CurrentDeflateTime = m_DeflateTime;
			++m_InflateStatus;
			m_HasInflationChanged = true;
		}
		else
		{
			m_CurrentInflateTime -= m_ElapsedTime;
		}
	}
}

void dae::AgentComponent::RockCollision()
{
	if (!m_IsInvis)
	{
		bool isHit = ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "Stone" },
			Rectf{ GetTransform()->GetPosition().x, GetTransform()->GetPosition().y,48.0f,48.0f });
		if(isHit && !m_IsHitByFallingRock)
		{
			m_IsHitByFallingRock = true;
			m_IsDead = true;
			if (ServiceLocator::GetTile(m_TileIndex)->Position.y > 624)
				m_pScore->onNotify(GetClosestPlayerIndex(), Observer::Event::ScoreRock4);
			else if(ServiceLocator::GetTile(m_TileIndex)->Position.y > 432)
				m_pScore->onNotify(GetClosestPlayerIndex(), Observer::Event::ScoreRock3);
			else if(ServiceLocator::GetTile(m_TileIndex)->Position.y > 240)
				m_pScore->onNotify(GetClosestPlayerIndex(), Observer::Event::ScoreRock2);
			else
			m_pScore->onNotify(GetClosestPlayerIndex(), Observer::Event::ScoreRock1);
		}
	}
}

void dae::AgentComponent::Inflate()
{
	if (m_InflateStatus > 0)
	{
		m_CurrentDeflateTime -= m_ElapsedTime;
		if (m_CurrentDeflateTime <= 0.0f)
		{
			--m_InflateStatus;
			if (m_InflateStatus > 0)
			{
				m_CurrentDeflateTime = m_DeflateTime;
				m_HasInflationChanged = true;
			}
			else
				m_IsBeingInflated = false;
		}
	}

	if (m_InflateStatus == m_MaxInflate)
	{
		if (ServiceLocator::GetTile(m_TileIndex)->Position.y > 624)
			m_pScore->onNotify(GetClosestPlayerIndex(), Observer::Event::ScoreNormal4);
		else if (ServiceLocator::GetTile(m_TileIndex)->Position.y > 432)
			m_pScore->onNotify(GetClosestPlayerIndex(), Observer::Event::ScoreNormal3);
		else if (ServiceLocator::GetTile(m_TileIndex)->Position.y > 240)
			m_pScore->onNotify(GetClosestPlayerIndex(), Observer::Event::ScoreNormal2);
		else
			m_pScore->onNotify(GetClosestPlayerIndex(), Observer::Event::ScoreNormal1);
		m_IsDead = true;
	}

	if (m_IsDead == false && m_HasInflationChanged)
	{
		if (GetGameObject()->HasComponent<SpriteComponent>())
		{
			if (m_EnemyType == EnemyType::Pooka)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(4 + m_InflateStatus);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(11 + m_InflateStatus);
		}
		m_HasInflationChanged = false;
	}
}

void dae::AgentComponent::Dead()
{
	
	if (GetGameObject()->HasComponent<SpriteComponent>())
	{
		if (m_EnemyType == EnemyType::Pooka)
			GetGameObject()->GetComponent<SpriteComponent>()->SetRow(3);
		else
			GetGameObject()->GetComponent<SpriteComponent>()->SetRow(10);
	}
	if (m_IsDead)
	{
		m_DeadTime -= m_ElapsedTime;
		if (m_DeadTime <= 0.0f)
		{
			if (GetGameObject()->HasComponent<SpriteComponent>())
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(20);
			m_IsActive = false;
		}

	}
}

void dae::AgentComponent::DisableCollision() const
{
	if (m_IsDead)
	{
		ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollsionIndex, false);
	}
}
