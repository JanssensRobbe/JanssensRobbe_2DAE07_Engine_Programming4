#include "pch.h"
#include "AgentComponent.h"
#include "State.h"
#include "Transition.h"
#include "Level.h"
#include "Structs.h"
#include "Actions.h"
#include "Conditions.h"
#include "PengoCharacterComponent.h"
#include "Locator.h"
#include "SpriteComponent.h"
#include <math.h>
#include "SceneManager.h"



int dae::AgentComponent::m_Count = 0;

dae::AgentComponent::AgentComponent(int gridSize, int nbColumns, dae::EnemyType enemyType, bool isInvisible)
	:m_GridSize{ gridSize }
	,m_NumberOfColumns{nbColumns}
	, m_EnemyType{ enemyType }
	, m_IsInvisible(isInvisible)
{
	auto boundries = SceneManager::GetInstance().GetBoundries();
	m_XLimits.x = boundries.left;
	m_XLimits.y = boundries.left + boundries.width - 48.0f;
	m_YLimits.x = boundries.bottom;
	m_YLimits.y = boundries.bottom + boundries.height;
}


void dae::AgentComponent::Update(float deltaTime)
{
	if (!m_UseRunningSpeed)
	{
		if (m_RunningSpeedTimer > 0.0f)
		{
			m_RunningSpeedTimer -= deltaTime;
		}
		else
			m_UseRunningSpeed = true;
	}
	if (!m_IsInvisible)
	{
		if (m_Direction == Direction::right || m_Direction == Direction::down)
			m_TileIndex = int(int(GetTransform()->GetPosition().x) / 48) + int(int(GetTransform()->GetPosition().y) / 48) * 14;
		else
			m_TileIndex = int(int(GetTransform()->GetPosition().x + 47) / 48) + int(int(GetTransform()->GetPosition().y + 47) / 48) * 14;

		if (!m_IsRegistered)
		{
			m_CollsionIndex = Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->AddCollider(Tag{ "Enemy" }, Rectf{ GetTransform()->GetPosition().x, GetTransform()->GetPosition().y, 48.0f,48.0f });
			m_IsRegistered = true;
		}
		else if (!m_IsDead)
			Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollsionIndex, Rectf{ GetTransform()->GetPosition().x, GetTransform()->GetPosition().y, 48.0f,48.0f });

		m_ElapsedTime = deltaTime;

		if (!m_Init)
			return;

		if (m_IsIdle)
		{
			if (m_InitIdleTime > 0.0f)
				m_InitIdleTime -= deltaTime;
			else if (m_InitIdleTime <= 0.0f)
			{
				m_IsIdle = false;
			}
		}
		if (m_IsActive)
			m_pStateMachine->Update(deltaTime);
		Collision();
	}
	else
	{
		GetGameObject()->GetComponent<SpriteComponent>()->SetActive(false);
	}
}

void dae::AgentComponent::Render()
{
}

void dae::AgentComponent::Initialize()
{
	// TODO fix animation going right
	State* run = new State{};
	State* dead = new State{};
	State* hitByRock = new State{};
	State* idle = new State{};
	State* stunned = new State{};
	State* chasing = new State{};

	idle->SetTransition(std::make_shared<Transition>(std::make_shared<StopBeingIdle>(), run));
	idle->SetTransition(std::make_shared<Transition>( std::make_shared<IsHitByRock>(), hitByRock));
	idle->SetTransition(std::make_shared<Transition>(std::make_shared<IsStunned>(), stunned));
	//inflate->SetAction(std::make_shared<InflateAction>(),dae::ActionName::Action);
	//inflate->SetTransition(std::make_shared<Transition>( std::make_shared<IsDead>() , dead));

	dead->SetAction(std::make_shared<DeadAction>(), dae::ActionName::Action);

	hitByRock->SetAction(std::make_shared<DisableCollisionAction>(), dae::ActionName::EntryAction);
	hitByRock->SetAction(std::make_shared<FollowRockAction>(), dae::ActionName::Action);
	hitByRock->SetTransition(std::make_shared<Transition>(std::make_shared<IsDead>(), dead));

	run->SetAction(std::make_shared<WalkAction>(), dae::ActionName::Action);
	run->SetTransition(std::make_shared<Transition>(std::make_shared<IsHitByRock>() , hitByRock));
	run->SetTransition(std::make_shared<Transition>(std::make_shared<IsStunned>(), stunned));
	run->SetTransition(std::make_shared<Transition>(std::make_shared<IsChasing>(), chasing));

	chasing->SetAction(std::make_shared<ChaseAction>(), dae::ActionName::Action);
	chasing->SetTransition(std::make_shared<Transition>(std::make_shared<StopChasing>(), run));
	chasing->SetTransition(std::make_shared<Transition>(std::make_shared<IsHitByRock>(), hitByRock));
	chasing->SetTransition(std::make_shared<Transition>(std::make_shared<IsStunned>(), stunned));


	stunned->SetAction(std::make_shared<StunAction>(), dae::ActionName::Action);
	stunned->SetTransition(std::make_shared<Transition>(std::make_shared<StopBeingStunned>(), run));
	stunned->SetTransition(std::make_shared<Transition>(std::make_shared<IsDead>(), dead));
	stunned->SetTransition(std::make_shared<Transition>(std::make_shared<IsHitByRock>(), hitByRock));

	m_pStateMachine = new StateMachine{ std::vector<State*>{run, dead, hitByRock, idle, stunned}, idle, m_Count };
	++m_Count;
	m_Init = true;
}

void dae::AgentComponent::Walk()
{
	auto pos = GetTransform()->GetPosition();
	m_Index = int(GetTransform()->GetPosition().x) / 48 + int(GetTransform()->GetPosition().y) / 48 * 14;
	if (GetClosestPlayerDistance() < 150.0f)
	{
		m_ChasePlayer = true;
	}
	if (m_UseRunningSpeed)
		m_MovementSpeed = m_RunningSpeed;

	switch (m_Direction)
	{
	case dae::Direction::right:
		if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" },Rectf{ pos.x + 48.0f,pos.y + 24.0f,4.0f,4.0f }) 
			&& pos.x + 8.0f < m_XLimits.y
			&& Locator::GetTile(m_TileIndex + 1)->tileName == TileName::Black)
			GetTransform()->SetPosition(pos.x + m_MovementSpeed * m_ElapsedTime, pos.y);
		else if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x + 24.0f,pos.y - 4.0f,4.0f,4.0f })
			&& Locator::GetTile(m_TileIndex - 14)->tileName == TileName::Black)
		{
			GetTransform()->SetPosition(float(((int(pos.x + 4.0f) / 48)) * 48), pos.y);
			m_Direction = Direction::up;
		}
		else if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x + 24.0f,pos.y + 48.0f,4.0f,4.0f })
			&& Locator::GetTile(m_TileIndex + 14)->tileName == TileName::Black)
		{
			GetTransform()->SetPosition(float(((int(pos.x + 4.0f) / 48)) * 48), pos.y);
			m_Direction = Direction::down;
		}
		else
		{
			m_Direction = Direction::left;
		}
		break;
	case dae::Direction::down:
		if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x + 24.0f,pos.y +  48.0f,4.0f,4.0f })
			&& pos.y + 8.0f < m_YLimits.y
			&& Locator::GetTile(m_TileIndex + 14)->tileName == TileName::Black)
			GetTransform()->SetPosition(pos.x, pos.y + m_MovementSpeed * m_ElapsedTime);
		else if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x - 4.0f,pos.y + 24.0f,4.0f,4.0f })
			&& Locator::GetTile(m_TileIndex - 1)->tileName == TileName::Black)
		{
			GetTransform()->SetPosition(pos.x, float(((int(pos.y + 4.0f) / 48)) * 48));
			m_Direction = Direction::left;
		}
		else if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x + 48.0f,pos.y + 24.0f,4.0f,4.0f })
			&& Locator::GetTile(m_TileIndex + 1)->tileName == TileName::Black)
		{
			GetTransform()->SetPosition(pos.x, float(((int(pos.y  + 4.0f) / 48)) * 48));
			m_Direction = Direction::right;
		}
		else
			m_Direction = Direction::up;
		break;
	case dae::Direction::left:
		if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x - 4.0f,pos.y + 24.0f,4.0f,4.0f })
			&& pos.x > m_XLimits.x
			&& Locator::GetTile(m_TileIndex - 1)->tileName == TileName::Black)
			GetTransform()->SetPosition(pos.x - m_MovementSpeed * m_ElapsedTime, pos.y);
		else if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x + 24.0f,pos.y - 4.0f,4.0f,4.0f })
			&& Locator::GetTile(m_TileIndex - 14)->tileName == TileName::Black)
		{
			m_Direction = Direction::up;
			GetTransform()->SetPosition(float((int(pos.x + 4.0f) / 48) * 48), pos.y);
		}
		else if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x + 24.0f,pos.y + 48.0f,4.0f,4.0f })
			&& Locator::GetTile(m_TileIndex + 14)->tileName == TileName::Black)
		{
			m_Direction = Direction::down;
			GetTransform()->SetPosition(float((int(pos.x + 4.0f) / 48) * 48), pos.y);
		}
		else
			m_Direction = Direction::right;
		break;
	case dae::Direction::up:
		if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x + 24.0f,pos.y - 4.0f,4.0f,4.0f })
			&& pos.y > m_YLimits.x
			&& Locator::GetTile(m_TileIndex - 14)->tileName == TileName::Black)
			GetTransform()->SetPosition(pos.x, pos.y - m_MovementSpeed * m_ElapsedTime);
		else if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x - 4.0f,pos.y + 24.0f,4.0f,4.0f })
			&& Locator::GetTile(m_TileIndex - 1)->tileName == TileName::Black)
		{
			m_Direction = Direction::left;
			GetTransform()->SetPosition(pos.x, float((int(pos.y + 4.0f) / 48) * 48));
		}
		else if (!Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ pos.x + 48.0f,pos.y + 24.0f,4.0f,4.0f })
			&& Locator::GetTile(m_TileIndex + 1)->tileName == TileName::Black)
		{
			m_Direction = Direction::right;
			GetTransform()->SetPosition(pos.x, float((int(pos.y + 4.0f) / 48) * 48));
		}
		else
			m_Direction = Direction::down;
		break;
	}

	UNREFERENCED_PARAMETER(pos);
	if (GetGameObject()->HasComponent<SpriteComponent>())
	{
		if (m_Direction == Direction::left)
		{
			if (!m_UseRunningSpeed)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(3);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(4);
		}
		if (m_Direction == Direction::right)
		{
			if (!m_UseRunningSpeed)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(0);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(1);
		}
		if (m_Direction == Direction::down)
		{
			if (!m_UseRunningSpeed)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(5);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(6);
		}
		if (m_Direction == Direction::up)
		{
			if (!m_UseRunningSpeed)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(7);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(8);
		}

	}
}

void dae::AgentComponent::GetClosestPlayer()
{
	auto pos = GetTransform()->GetPosition();
	m_Index = int(GetTransform()->GetPosition().x + 24.0f) / 48 + int(GetTransform()->GetPosition().y + 24.0f) / 48 * 14;

	for (auto stone : Locator::Getwalls())
	{
		if (!stone.second->GetBonusBlock() && !stone.second->GetIsMoving() && !stone.second->GetIsDead())
		{
			if (m_Index == stone.second->GetIndex())
			{
				stone.second->DeleteWall();
			}
		}
	}

	if (!m_IsInGrid)
	{
		switch (m_Direction)
		{
		case dae::Direction::right:
			GetTransform()->SetPosition(pos.x + m_MovementSpeed * m_ElapsedTime, pos.y);
			if (pos.x < int(m_Index % 14) * m_GridSize + 0.5f && pos.x > int(m_Index % 14) * m_GridSize - 0.5f)
			{
				GetTransform()->SetPosition(float(int(m_Index % 14) * m_GridSize), pos.y);
				m_IsInGrid = true;
			}
			break;
		case dae::Direction::down:
			GetTransform()->SetPosition(pos.x, pos.y + m_MovementSpeed * m_ElapsedTime);
			if (pos.y < int(m_Index / 14) * m_GridSize + 0.5f && pos.y > int(m_Index / 14) * m_GridSize - 0.5f)
			{
				GetTransform()->SetPosition(pos.x, float(int(m_Index / 14) * m_GridSize));
				m_IsInGrid = true;
			}
			break;
		case dae::Direction::left:
			GetTransform()->SetPosition(pos.x - m_MovementSpeed * m_ElapsedTime, pos.y);
			if (pos.x < int(m_Index % 14) * m_GridSize + 0.5f && pos.x > int(m_Index % 14) * m_GridSize - 0.5f)
			{
				GetTransform()->SetPosition(float(int(m_Index % 14) * m_GridSize), pos.y);
				m_IsInGrid = true;
			}
			break;
		case dae::Direction::up:
			GetTransform()->SetPosition(pos.x, pos.y - m_MovementSpeed * m_ElapsedTime);
			if (pos.y < int(m_Index / 14) * m_GridSize + 0.5f && pos.y > int(m_Index / 14) * m_GridSize - 0.5f)
			{
				GetTransform()->SetPosition(pos.x, float(int(m_Index / 14) * m_GridSize));
				m_IsInGrid = true;
			}
			break;
		default:
			break;
		}
	}
	if (!m_ChosenDirection && m_IsInGrid)
	{
		if (int(m_Index / 14) < int(GetClosestPlayerTileIndex() / 14))
		{
			m_Direction = Direction::down;
			GetTransform()->SetPosition(pos.x, pos.y + m_MovementSpeed * m_ElapsedTime);
		}
		else if (int(m_Index / 14) > int(GetClosestPlayerTileIndex() / 14))
		{
			m_Direction = Direction::up;
			GetTransform()->SetPosition(pos.x, pos.y - m_MovementSpeed * m_ElapsedTime);
		}
		else
		{
			if (int(m_Index % 14) < int(GetClosestPlayerTileIndex() % 14))
			{
				m_Direction = Direction::right;
				GetTransform()->SetPosition(pos.x + m_MovementSpeed * m_ElapsedTime, pos.y);
			}
			else if (int(m_Index % 14) > int(GetClosestPlayerTileIndex() % 14))
			{
				m_Direction = Direction::left;
				GetTransform()->SetPosition(pos.x - m_MovementSpeed * m_ElapsedTime, pos.y);
			}
		}
		m_ChosenDirection = true;
	}
	else if(m_ChosenDirection && m_IsInGrid)
	{
		switch (m_Direction)
		{
		case Direction::down:
			GetTransform()->SetPosition(pos.x, pos.y + m_MovementSpeed * m_ElapsedTime);
			if (pos.y < int(m_Index / 14) * m_GridSize + 0.5f && pos.y > int(m_Index / 14) * m_GridSize - 0.5f)
			{
				GetTransform()->SetPosition(pos.x,float(int(m_Index/14) * m_GridSize));
				m_ChosenDirection = false;
			}
			break;
		case Direction::up:
			GetTransform()->SetPosition(pos.x, pos.y - m_MovementSpeed * m_ElapsedTime);
			if (pos.y < int(m_Index / 14) * m_GridSize + 0.5f && pos.y > int(m_Index / 14) * m_GridSize - 0.5f)
			{
				GetTransform()->SetPosition(pos.x, float(int(m_Index / 14) * m_GridSize));
				m_ChosenDirection = false;
			}
			break;
		case Direction::left:
			GetTransform()->SetPosition(pos.x - m_MovementSpeed * m_ElapsedTime, pos.y);
			if (pos.x < int(m_Index % 14) * m_GridSize + 0.5f && pos.x > int(m_Index % 14) * m_GridSize - 0.5f)
			{
				GetTransform()->SetPosition(float(int(m_Index % 14) * m_GridSize),pos.y);
				m_ChosenDirection = false;
			}
			break;
		case Direction::right:
			GetTransform()->SetPosition(pos.x + m_MovementSpeed * m_ElapsedTime, pos.y);
			if (pos.x < int(m_Index % 14) * m_GridSize + 0.5f && pos.x > int(m_Index % 14) * m_GridSize - 0.5f)
			{
				GetTransform()->SetPosition(float(int(m_Index % 14) * m_GridSize), pos.y);
				m_ChosenDirection = false;
			}
			break;
		default:
			break;
		}
	}

	if (GetClosestPlayerDistance() > 150.0f)
	{
		m_ChasePlayer = false;
	}

	if (GetGameObject()->HasComponent<SpriteComponent>())
	{
		if (m_Direction == Direction::left)
		{
			if (!m_UseRunningSpeed)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(3);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(4);
		}
		if (m_Direction == Direction::right)
		{
			if (!m_UseRunningSpeed)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(0);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(1);
		}
		if (m_Direction == Direction::down)
		{
			if (!m_UseRunningSpeed)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(5);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(6);
		}
		if (m_Direction == Direction::up)
		{
			if (!m_UseRunningSpeed)
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(7);
			else
				GetGameObject()->GetComponent<SpriteComponent>()->SetRow(8);
		}
	}
}
void dae::AgentComponent::Stun()
{
	GetGameObject()->GetComponent<SpriteComponent>()->SetRow(9);
	if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "player" }, Rectf{ GetTransform()->GetPosition().x + 20.0f, GetTransform()->GetPosition().y + 20.0f,4.0f,4.0f }))
	{
		m_IsDead = true;
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
	auto& players = Locator::GetPlayers();
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
		return x + y * m_NumberOfColumns;
	}
	return -1;
}

int dae::AgentComponent::GetClosestPlayerIndex() const
{
	auto& players = Locator::GetPlayers();
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
	auto& players = Locator::GetPlayers();
	float closestDist = -1.0f;
	for (const auto player : players)
	{
		if (player.second->GetComponent<PengoCharacterComponent>()->GetIsDead())
			continue;
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
		bool isHit =  Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
			Rectf{ GetTransform()->GetPosition().x + 12.0f, GetTransform()->GetPosition().y + 12.0f,24.0f,24.0f });
		if(isHit)
			{ 
			if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
				Rectf{ GetTransform()->GetPosition().x - 4.0f, GetTransform()->GetPosition().y + 22.0f,4.0f,4.0f }))
			{
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
					Rectf{ GetTransform()->GetPosition().x, GetTransform()->GetPosition().y - 16.0f,4.0f,4.0f }))
				{
					m_HitDirection = Direction::down;
				}
				else if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
					Rectf{ GetTransform()->GetPosition().x, GetTransform()->GetPosition().y + 60.0f,4.0f,4.0f }))
				{
					m_HitDirection = Direction::up;
				}
				else
					m_HitDirection = Direction::right;
			}
			if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
				Rectf{ GetTransform()->GetPosition().x + 48.0f, GetTransform()->GetPosition().y + 22.0f,4.0f,4.0f }))
			{
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
					Rectf{ GetTransform()->GetPosition().x + 44.0f, GetTransform()->GetPosition().y - 16.0f,4.0f,4.0f }))
				{
					m_HitDirection = Direction::down;
				}
				else if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
					Rectf{ GetTransform()->GetPosition().x + 44.0f, GetTransform()->GetPosition().y + 60.0f,4.0f,4.0f }))
				{
					m_HitDirection = Direction::up;
				}
				else
					m_HitDirection = Direction::left;
			}
			if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
				Rectf{ GetTransform()->GetPosition().x + 22.0f, GetTransform()->GetPosition().y - 4.0f,4.0f,4.0f }))
			{
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
					Rectf{ GetTransform()->GetPosition().x + 60.0f, GetTransform()->GetPosition().y,4.0f,4.0f }))
				{
					m_HitDirection = Direction::left;
				}
				else if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
					Rectf{ GetTransform()->GetPosition().x - 16.0f, GetTransform()->GetPosition().y,4.0f,4.0f }))
				{
					m_HitDirection = Direction::right;
				}
				else
					m_HitDirection = Direction::down;
			}
			if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
				Rectf{ GetTransform()->GetPosition().x + 22.0f, GetTransform()->GetPosition().y + 48.0f,4.0f,4.0f }))
			{
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
					Rectf{ GetTransform()->GetPosition().x + 60.0f, GetTransform()->GetPosition().y + 44.0f,4.0f,4.0f }))
				{
					m_HitDirection = Direction::left;
				}
				else if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "MovingStone" },
					Rectf{ GetTransform()->GetPosition().x - 16.0f, GetTransform()->GetPosition().y + 44.0f,4.0f,4.0f }))
				{
					m_HitDirection = Direction::right;
				}
				else
					m_HitDirection = Direction::up;
			}
			m_IsHitByFlyingRock = true;
		}
	}
}


void dae::AgentComponent::Dead()
{
	m_IsActive = false;
	if(GetGameObject()->HasComponent<SpriteComponent>())
		GetGameObject()->GetComponent<SpriteComponent>()->SetActive(false);
	Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollsionIndex, false);
	if(m_IsStunned)
		Locator::GetSubject()->SetEvent(dae::Subject::Event::EnemyX2);
	else
		Locator::GetSubject()->SetEvent(dae::Subject::Event::EnemyX1);
	Locator::GetSubject()->SetScoreChanged(true);
}

void dae::AgentComponent::FollowRock()
{
	if (m_IsHitByFlyingRock)
	{
		if (GetGameObject()->HasComponent<SpriteComponent>())
			GetGameObject()->GetComponent<SpriteComponent>()->SetRow(9);
		auto movementSpeed = 150.0f;
		switch (m_HitDirection)
		{
		case Direction::right:
			GetTransform()->SetPosition(GetTransform()->GetPosition().x + m_ElapsedTime * movementSpeed, GetTransform()->GetPosition().y);
			break;
		case Direction::left:
			GetTransform()->SetPosition(GetTransform()->GetPosition().x - m_ElapsedTime * movementSpeed, GetTransform()->GetPosition().y);
			break;
		case Direction::down:
			GetTransform()->SetPosition(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y + m_ElapsedTime * movementSpeed);
			break;
		case Direction::up:
			GetTransform()->SetPosition(GetTransform()->GetPosition().x, GetTransform()->GetPosition().y - m_ElapsedTime * movementSpeed);
			break;
		}
		auto boundries = SceneManager::GetInstance().GetBoundries();
		if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ GetTransform()->GetPosition().x + 24.0f ,GetTransform()->GetPosition().y + 24.0f,4.0f,4.0f }) 
			|| GetTransform()->GetPosition().x + 22.0f < boundries.left
			|| GetTransform()->GetPosition().x + 22.0f > boundries.left + boundries.width
			|| GetTransform()->GetPosition().y + 22.0f < boundries.bottom
			|| GetTransform()->GetPosition().y > boundries.bottom + boundries.height)
		{
			m_IsDead = true;
		}
	}
}

void dae::AgentComponent::DisableCollision() const
{
		Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollsionIndex, false);
}
