#include "pch.h"
#include "MovableWallComponent.h"
#include "TextureComponent.h"
#include "Locator.h"
#include "PengoCharacterComponent.h"
#include "AgentComponent.h"
#include "TextureComponent.h"

dae::MovableWallComponent::MovableWallComponent(std::string nameTexture, int index, bool isEnemyTile)
	:BaseComponent{}
	, m_pTexture{ new TextureComponent{nameTexture} }
	,m_Index{index}
	,m_isMoving{false}
	, m_MovingDirection{Direction::none}
	, m_MovementSpeed{150.0f}
	, m_IsRegistered{false}
	, m_CollisionIndex{}
	, m_IsDead{false}
	, m_TimerBeforeFall{1.0f}
	, m_StartTimer{ false }
	, m_IsSideChecked{false}
	, m_IsDisabled{false}
	, m_MovingStoneIndex{0}
	, m_IsEnemyTile{isEnemyTile}
	, m_IsBonusTile{false}
	, m_IsSpecialActive{false}
{
	
	m_Position = Locator::GetTile(m_Index)->Position;
	m_pPlayers = Locator::GetPlayers();
}

dae::MovableWallComponent::~MovableWallComponent()
{
	delete m_pTexture;
}

void dae::MovableWallComponent::Update(float deltaTime)
{
	if (!m_IsDisabled)
	{
		if (m_IsSpecialActive)
		{
			m_SpecialTimer -= deltaTime;
			if (m_SpecialTimer < 0.0f)
			{
				m_IsSpecialActive = false;
				for (auto agent : Locator::GetAgents())
				{
					agent.second->GetComponent<AgentComponent>()->m_IsStunned = false;
				}
			}
		}
		m_pPlayers = Locator::GetPlayers();

		m_ShowEggTimer -= deltaTime;
		//if (m_StartTimer && m_TimerBeforeFall > 0.0f)
		//	m_TimerBeforeFall -= deltaTime;
		//else if (m_TimerBeforeFall <= 0.0f)
		//	m_IsFalling = true;

		//TODO: Check if player is pushing
		//TODO: Check idle position
		//TDOO: check the rock in that direction
		//TODO: make it move
		
		if (!m_IsRegistered)
		{
			m_CollisionIndex = Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->AddCollider(Tag{ "stone" }, Rectf{ m_Position.x,m_Position.y,48.0f,48.0f });
			m_MovingStoneIndex = Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->AddCollider(Tag{ "MovingStone" }, Rectf{ m_Position.x,m_Position.y,48.0f,48.0f });
			Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_MovingStoneIndex, false);
			m_IsRegistered = true;
		}
		for (auto player : m_pPlayers)
		{
			if (player.second->HasComponent<PengoCharacterComponent>())
			{
				if (player.second->GetComponent<PengoCharacterComponent>()->GetIsPushing())
				{
					
					switch (player.second->GetComponent<PengoCharacterComponent>()->GetIdleDirection())
					{

					case Direction::right:
						if ((int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().x + 8.0f) / 48 + int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().y + 8.0f) / 48 * 14) + 1 == m_Index
							&& m_Position.x + 1.0f < m_Boundries.left + m_Boundries.width - 48.0f)
						{
							m_MovingDirection = Direction::right;
							m_isMoving = true;
						}
						else if ((int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().x + 8.0f) / 48 + int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().y + 8.0f) / 48 * 14) + 1 == m_Index
							  && m_Position.x + 1.0f > m_Boundries.left + m_Boundries.width - 48.0f && !m_IsBonusTile)
						{
							if (m_IsEnemyTile)
							{
								Locator::GetSubject()->SetEvent(dae::Subject::Event::Nest);
								Locator::GetSubject()->SetScoreChanged(true);
							}
							m_IsDisabled = true;
							m_Position.x = -48.0f;
							m_Position.y = -48.0f;
							Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex, false);
						}
						break;
					case Direction::left:
						if ((int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().x + 40.0f) / 48 + int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().y + 8.0f) / 48 * 14) - 1 == m_Index
							&& m_Position.x - 1.0f > m_Boundries.left)
						{
							m_MovingDirection = Direction::left;
							m_isMoving = true;
						}
						else if ((int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().x + 40.0f) / 48 + int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().y + 8.0f) / 48 * 14) - 1 == m_Index
							&& m_Position.x - 1.0f < m_Boundries.left && ! m_IsBonusTile)
						{
							if (m_IsEnemyTile)
							{
								Locator::GetSubject()->SetEvent(dae::Subject::Event::Nest);
								Locator::GetSubject()->SetScoreChanged(true);
							}
							m_IsDisabled = true;
							m_Position.x = -48.0f;
							m_Position.y = -48.0f;
							Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex, false);
						}
						break;
					case Direction::up:
						if ((int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().x + 8.0f) / 48 + int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().y + 40.0f) / 48 * 14) - 14 == m_Index
							&& m_Position.y - 1.0f > m_Boundries.bottom)
						{

							m_MovingDirection = Direction::up;
							m_isMoving = true;
						}
						else if ((int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().x + 8.0f) / 48 + int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().y + 40.0f) / 48 * 14) - 14 == m_Index
							&& m_Position.y - 1.0f < m_Boundries.bottom && !m_IsBonusTile)
						{
							if (m_IsEnemyTile)
							{
								Locator::GetSubject()->SetEvent(dae::Subject::Event::Nest);
								Locator::GetSubject()->SetScoreChanged(true);
							}
							m_IsDisabled = true;
							m_Position.x = -48.0f;
							m_Position.y = -48.0f;
							Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex, false);
						}
						break;
					case Direction::down:
						if ((int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().x + 8.0f) / 48 + int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().y + 8.0f) / 48 * 14) + 14 == m_Index
							&& m_Position.y + 1.0f < m_Boundries.bottom + m_Boundries.height - 48.0f)
						{
							m_MovingDirection = Direction::down;
							m_isMoving = true;
						}
						else if ((int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().x + 8.0f) / 48 + int(player.second->GetComponent<PengoCharacterComponent>()->GetPosition().y + 8.0f) / 48 * 14) + 14 == m_Index
							&& m_Position.y + 1.0f > m_Boundries.bottom + m_Boundries.height - 48.0f && !m_IsBonusTile)
						{
							if (m_IsEnemyTile)
							{
								Locator::GetSubject()->SetEvent(dae::Subject::Event::Nest);
								Locator::GetSubject()->SetScoreChanged(true);
							}
							m_IsDisabled = true;
							m_Position.x = -48.0f;
							m_Position.y = -48.0f;
							Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex, false);
						}
							
						break;
					default:
						break;
					}
				}
			}
		}

		//TODO: ADD WALL END LEVEL REQ IF ALREADY MOVING
		if (m_isMoving && !m_IsSideChecked)
		{
			Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex, false);
			Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_MovingStoneIndex, true);

			switch (m_MovingDirection)
			{
			case dae::Direction::right:
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_Position.x + 50.0f, m_Position.y + 24.0f,4.0f,4.0f }) || m_Position.x + 52.0f > m_Boundries.left + m_Boundries.width)
				{
					if (!m_IsBonusTile)
					{
						if (m_IsEnemyTile)
						{
							Locator::GetSubject()->SetEvent(dae::Subject::Event::Nest);
							Locator::GetSubject()->SetScoreChanged(true);
						}
						m_IsDisabled = true;
						m_Position.x = -48.0f;
						m_Position.y = -48.0f;
					}
					else
					{
						m_isMoving = false;
					}
				}
				break;
			case dae::Direction::down:
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_Position.x + 24.0f, m_Position.y + 50.0f,4.0f,4.0f }) || m_Position.y + 52.0f > m_Boundries.bottom + m_Boundries.height)
				{
					if (!m_IsBonusTile)
					{
						if (m_IsEnemyTile)
						{
							Locator::GetSubject()->SetEvent(dae::Subject::Event::Nest);
							Locator::GetSubject()->SetScoreChanged(true);
						}
						m_IsDisabled = true;
						m_Position.x = -48.0f;
						m_Position.y = -48.0f;
					}
					else
					{
						m_isMoving = false;
					}
				}
				break;
			case dae::Direction::left:
				m_Position.x -= deltaTime * m_MovementSpeed;
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_Position.x - 4.0f, m_Position.y + 24.0f,4.0f,4.0f }) ||  m_Position.x - 4.0f < m_Boundries.left)
				{
					if (!m_IsBonusTile)
					{
						if (m_IsEnemyTile)
						{
							Locator::GetSubject()->SetEvent(dae::Subject::Event::Nest);
							Locator::GetSubject()->SetScoreChanged(true);
						}
						m_IsDisabled = true;
						m_Position.x = -48.0f;
						m_Position.y = -48.0f;
					}
					else
					{
						m_isMoving = false;
					}
				}
				break;
			case dae::Direction::up:
				m_Position.y -= deltaTime * m_MovementSpeed;
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_Position.x + 24.0f, m_Position.y - 4.0f,4.0f,4.0f }) || m_Position.y - 4.0f < m_Boundries.bottom)
				{
					if (!m_IsBonusTile)
					{
						if (m_IsEnemyTile)
						{
							Locator::GetSubject()->SetEvent(dae::Subject::Event::Nest);
							Locator::GetSubject()->SetScoreChanged(true);
						}
						m_IsDisabled = true;
						m_Position.x = -48.0f;
						m_Position.y = -48.0f;
					}
					else
					{
						m_isMoving = false;
					}
				}
				break;
			}
			m_IsSideChecked = true;
		}
		if (!m_isMoving && !m_IsDisabled)
		{
			Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_MovingStoneIndex, false);
			Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex, true);
		}
		if (m_isMoving)
		{
			switch (m_MovingDirection)
			{
			case dae::Direction::right:
				m_Position.x += deltaTime * m_MovementSpeed;
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_Position.x + 48.0f, m_Position.y + 24.0f,4.0f,4.0f })
					|| m_Position.x + 1.0f > m_Boundries.left + m_Boundries.width - 48.0f)
				{
					m_isMoving = false;
					m_IsSideChecked = false;
					m_Position.x = (int(m_Position.x + 4.0f) / 48) * 48.0f;
					m_Position.y = (int(m_Position.y) / 48) * 48.0f;
				}
				break;
			case dae::Direction::down:
				m_Position.y += deltaTime * m_MovementSpeed;
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_Position.x + 24.0f, m_Position.y + 48.0f,4.0f,4.0f })
					|| m_Position.y + 1.0f > m_Boundries.bottom + m_Boundries.height - 48.0f)\
				{
					m_isMoving = false;
					m_IsSideChecked = false;
					m_Position.x = (int(m_Position.x) / 48) * 48.0f;
					m_Position.y = (int(m_Position.y + 4.0f) / 48) * 48.0f;
				}
				break;
			case dae::Direction::left:
				m_Position.x -= deltaTime * m_MovementSpeed;
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_Position.x - 4.0f, m_Position.y + 24.0f,4.0f,4.0f })
					|| m_Position.x - 1.0f < m_Boundries.left)
				{
					m_isMoving = false;
					m_IsSideChecked = false;
						m_Position.x = (int(m_Position.x + 8.0f) / 48) * 48.0f;
						m_Position.y = (int(m_Position.y) / 48) * 48.0f;
				}
				break;
			case dae::Direction::up:
				m_Position.y -= deltaTime * m_MovementSpeed;
				if (Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_Position.x + 24.0f, m_Position.y - 4.0f,4.0f,4.0f })
					|| m_Position.y - 1.0f < m_Boundries.bottom)
				{
					m_isMoving = false;
					m_IsSideChecked = false;
					m_Position.x = (int(m_Position.x) / 48) * 48.0f;
					m_Position.y = (int(m_Position.y + 8.0f) / 48) * 48.0f;
				}
				break;
			}
			Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_MovingStoneIndex, Rectf{ m_Position.x,m_Position.y,48.0f,48.0f });
			Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollisionIndex, Rectf{ m_Position.x,m_Position.y,48.0f,48.0f });
				
			m_Index = int(m_Position.x) / 48 + int(m_Position.y) / 48 * 14;
		}
	}
}

void dae::MovableWallComponent::Render()
{
	if (m_IsBonusTile)
	{
		if(!m_IsSpecialActive)
			m_pTexture->Render(Rectf{ m_Position.x,m_Position.y,48.0f,48.0f }, Rectf{ 32.0f,0.0f,16.0f,16.0f });
		else
			m_pTexture->Render(Rectf{ m_Position.x,m_Position.y,48.0f,48.0f }, Rectf{ 96.0f,0.0f,16.0f,16.0f });
	}
	else if (!m_IsEnemyTile || m_ShowEggTimer <= 0.0f)
	{
		if (!m_IsSpecialActive)
			m_pTexture->Render(Rectf{ m_Position.x,m_Position.y,48.0f,48.0f }, Rectf{ 16.0f,0.0f,16.0f,16.0f });
		else
			m_pTexture->Render(Rectf{ m_Position.x,m_Position.y,48.0f,48.0f }, Rectf{ 80.0f,0.0f,16.0f,16.0f });
	}
	else
		m_pTexture->Render(Rectf{ m_Position.x,m_Position.y,48.0f,48.0f }, Rectf{ 48.0f,0.0f,16.0f,16.0f });
}

Point2f dae::MovableWallComponent::GetSpawnEggLocation()
{
	if (!m_IsDisabled && m_IsEnemyTile)
	{
		return m_Position;
	}
	return Point2f{ 0,0 };
}

void dae::MovableWallComponent::DeleteWall() {
	if (!m_IsBonusTile && !m_IsDisabled)
	{
		if (m_IsEnemyTile)
		{
			Locator::GetSubject()->SetEvent(dae::Subject::Event::EnemyNest);
			Locator::GetSubject()->SetScoreChanged(true);
		}
		m_Position.x = -48.0f;
		m_Position.y = -48.0f;
		m_IsDisabled = true;
		Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollisionIndex, Rectf{ m_Position.x,m_Position.y,48.0f,48.0f });
	}
}
