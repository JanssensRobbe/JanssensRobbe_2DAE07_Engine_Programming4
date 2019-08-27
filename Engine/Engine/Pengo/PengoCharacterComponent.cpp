#include "pch.h"
#include "CharacterComponent.h"
#include "PengoCharacterComponent.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "Level.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Command.h"
#include "Locator.h"
#include "HealthComponent.h"
#include "StartMenuScene.h"
#include "AgentComponent.h"
#include "ResourceManager.h"

dae::PengoCharacterComponent::PengoCharacterComponent(DWORD playerNumber, SpriteComponent& spriteComponent, Point2f respawnPoint, dae::SceneType endscreenType)
	:CharacterComponent{playerNumber,spriteComponent}
	, m_PlayerPos{ 0.0f,0.0f }
	, m_HorizontalDirection{ dae::Direction::right }
	, m_VerticalDirection{ dae::Direction::down }
	, m_UseVerticalDirection{ false }
	, m_MovementSpeed{ 130.0f }
	, m_IsDead{false}
	, m_IsGameOver{false}
	, m_IsRegistered{false}
	, m_IsBlockMoving{false}
	, m_CollisionIndex{}
	, m_IsDeadTimer{1.0f}
	, m_RespawnLocation{respawnPoint}
	, m_SceneType{endscreenType}
{
	auto boundries = SceneManager::GetInstance().GetBoundries();
	m_XLimits.x = boundries.left;
	m_XLimits.y = boundries.left + boundries.width - 48.0f;
	m_YLimits.x = boundries.bottom;
	m_YLimits.y = boundries.bottom + boundries.height;
	m_CollisionIndex = Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->AddCollider(Tag{ "player" }, Rectf{ m_PlayerPos.x,m_PlayerPos.y,48.0f,48.0f });
}

void dae::PengoCharacterComponent::Update(float elapsedTime)
{
if(!m_IsDead)
{
	Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollisionIndex, Rectf{ m_PlayerPos.x,m_PlayerPos.y,48.0f,48.0f });
	m_PlayerPos = GetTransform()->GetPosition();
	UNREFERENCED_PARAMETER(elapsedTime);
	if (!Locator::GetAgent(AgentComponent::GetCount() - 4)->GetComponent<AgentComponent>()->m_IsStunned)
	{
		CheckEnemyCollision();
	}
	//CheckStoneCollision();
	m_pCommand = InputManager::GetInstance().handleInput(GamepadIndex(GetPlayerNumber()));
	m_pCommand->execute((*GetGameObject()));
	float newPos{};
	newPos = m_MovementSpeed * elapsedTime;

	if (m_IsPushing)
	{
		int index = int(m_PlayerPos.x) / 48 + (int(m_PlayerPos.y) / 48) * 14;
		std::cout << index << std::endl;
	}
	if (!m_UseIdle)
	{
		if (m_HorizontalDirection == Direction::right && !m_UseVerticalDirection)
		{
			if (m_PlayerPos.x + newPos < m_XLimits.y
				&& int(m_PlayerPos.y) % 48 == 0) {
				m_UseVerticalDirectionSprite = false;
				if (!CheckBlockCollsion(newPos, m_HorizontalDirection))
				{
					GetTransform()->SetPosition(m_PlayerPos.x + newPos, m_PlayerPos.y);
				}
			}
			else if (m_PlayerPos.x + newPos >= m_XLimits.y)
				GetTransform()->SetPosition(m_XLimits.y, m_PlayerPos.y);
			else if (int(m_PlayerPos.y) % 48 != 0)
			{
				m_UseVerticalDirectionSprite = true;
				if (int(m_PlayerPos.y) % 48 < 3)
				{
					GetTransform()->SetPosition(m_PlayerPos.x, int(m_PlayerPos.y / 48.0f)*48.0f);
				}
				else
				{
					if (m_VerticalDirection == Direction::up)
						GetTransform()->SetPosition(m_PlayerPos.x, m_PlayerPos.y - newPos);
					else if (m_VerticalDirection == Direction::down)
						GetTransform()->SetPosition(m_PlayerPos.x, m_PlayerPos.y + newPos);
				}
			}
		}
		else if (m_HorizontalDirection == Direction::left && !m_UseVerticalDirection)
		{
			if (m_PlayerPos.x + newPos > m_XLimits.x
				&& int(m_PlayerPos.y) % 48 == 0) {
				if (!CheckBlockCollsion(newPos, m_HorizontalDirection))
				{
					GetTransform()->SetPosition(m_PlayerPos.x - newPos, m_PlayerPos.y);
				}
				m_UseVerticalDirectionSprite = false;
			}
			else if (m_PlayerPos.x + newPos < m_XLimits.x)
				GetTransform()->SetPosition(m_XLimits.x, m_PlayerPos.y);
			else if (int(m_PlayerPos.y) % 48 != 0)
			{
				m_UseVerticalDirectionSprite = true;
				if (int(m_PlayerPos.y) % 48 < 3)
				{
					GetTransform()->SetPosition(m_PlayerPos.x, int(m_PlayerPos.y / 48.0f)*48.0f);
				}
				else
				{
					if (m_VerticalDirection == Direction::up)
						GetTransform()->SetPosition(m_PlayerPos.x, m_PlayerPos.y - newPos);
					else if (m_VerticalDirection == Direction::down)
						GetTransform()->SetPosition(m_PlayerPos.x, m_PlayerPos.y + newPos);
				}
			}

		}
		else if (m_VerticalDirection == Direction::up && m_UseVerticalDirection)
		{
			if (m_PlayerPos.y - newPos > m_YLimits.x
				&& int(m_PlayerPos.x) % 48 == 0) {
				if (!CheckBlockCollsion(newPos, m_VerticalDirection))
				{
					GetTransform()->SetPosition(m_PlayerPos.x, m_PlayerPos.y - newPos);
				}
				m_UseVerticalDirectionSprite = true;
			}
			else if (m_PlayerPos.y + newPos < m_YLimits.x)
				GetTransform()->SetPosition(m_PlayerPos.x, m_YLimits.x);
			else if (int(m_PlayerPos.x) % 48 != 0)
			{
				m_UseVerticalDirectionSprite = false;
				if (int(m_PlayerPos.x) % 48 < 3)
				{
					GetTransform()->SetPosition(int(m_PlayerPos.x / 48.0f)*48.0f, m_PlayerPos.y);
				}
				else
				{
					if (m_HorizontalDirection == Direction::left)
					{
						GetTransform()->SetPosition(m_PlayerPos.x - newPos, m_PlayerPos.y);
					}
					else if (m_HorizontalDirection == Direction::right)
					{
						GetTransform()->SetPosition(m_PlayerPos.x + newPos, m_PlayerPos.y);
					}
				}
			}
		}
		else if (m_VerticalDirection == Direction::down && m_UseVerticalDirection)
		{
			if (m_PlayerPos.y + newPos < m_YLimits.y
				&& int(m_PlayerPos.x) % 48 == 0) {
				if (!CheckBlockCollsion(newPos, m_VerticalDirection))
				{
					GetTransform()->SetPosition(m_PlayerPos.x, m_PlayerPos.y + newPos);
				}
				m_UseVerticalDirectionSprite = true;
			}
			else if (m_PlayerPos.y + newPos >= m_YLimits.y)
				GetTransform()->SetPosition(m_PlayerPos.x, m_YLimits.y);
			else if (int(m_PlayerPos.x) % 48 != 0)
			{
				m_UseVerticalDirectionSprite = false;
				if (int(m_PlayerPos.x) % 48 < 3)
				{
					GetTransform()->SetPosition(int(m_PlayerPos.x / 48.0f)*48.0f, m_PlayerPos.y);
				}
				else
				{
					if (m_HorizontalDirection == Direction::left)
					{
						GetTransform()->SetPosition(m_PlayerPos.x - newPos, m_PlayerPos.y);
					}
					else if (m_HorizontalDirection == Direction::right)
					{
						GetTransform()->SetPosition(m_PlayerPos.x + newPos, m_PlayerPos.y);
					}
				}
			}
		}
	}
}
	if (m_IsDead && !m_IsGameOver && m_IsDeadTimer <= 0.0f)
	{
		Reset();
		m_IsDead = false;
		m_IsDeadTimer = 1.0f;
	}
	else if (m_IsDead && !m_IsGameOver)
	{
		m_IsDeadTimer -= elapsedTime;
		return;
	}
	else if (m_IsDead && m_IsGameOver)
	{

		if (m_SceneType == SceneType::StartMenu)
		{
			auto scene = std::make_shared<StartMenuScene>("GameOverScene");
			SceneManager::GetInstance().CreateScene(m_SceneType, scene);
			SceneManager::GetInstance().DeleteScene("OnePlayer");
			SceneManager::GetInstance().DeleteScene("TwoPlayer");
			SceneManager::GetInstance().DeleteScene("Player");
			SceneManager::GetInstance().SetActiveScene(scene);
			
		}
	}
}


bool dae::PengoCharacterComponent::CheckBlockCollsion(float newPos, Direction direction)
{
	switch (direction)
	{
	case dae::Direction::right:
		return Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_PlayerPos.x + newPos + 32.0f, m_PlayerPos.y + 16.0f,16.0f,16.0f });
		break;
	case dae::Direction::down:
		return Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_PlayerPos.x + 16.0f, m_PlayerPos.y + newPos + 32.0f,16.0f,16.0f });
		break;
	case dae::Direction::left:
		return Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_PlayerPos.x - newPos, m_PlayerPos.y + 16.0f,16.0f,16.0f });
		break;
	case dae::Direction::up:
		return Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_PlayerPos.x + 16.0f, m_PlayerPos.y - newPos,16.0f,16.0f });
		break;
	case dae::Direction::none:
		return Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "stone" }, Rectf{ m_PlayerPos.x, m_PlayerPos.y,48.0f,48.0f });
		break;
	default:
		return false;
		break;
	}
	
}
void dae::PengoCharacterComponent::CheckEnemyCollision()
{
	auto isHit = Locator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "Enemy" }, Rectf{ m_PlayerPos.x + 16.0f, m_PlayerPos.y + 16.0f,16.0f,16.0f });
	if (isHit && !m_IsDead)
	{
		m_IsDead = true;
		if (GetGameObject()->GetComponent<HealthComponent>()->DecreaseHealth() == 0)
		{
			m_IsGameOver = true;
		}
	}
}

void dae::PengoCharacterComponent::Render()
{
	if (m_IsDead)
	{
		GetSprite()->SetRow(13);
		return;
	}
	if (!m_UseIdle)
	{
		if (m_UseVerticalDirectionSprite)
		{
			switch (m_VerticalDirection)
			{
			case dae::Direction::down:
				GetSprite()->SetRow(8);
				break;
			case dae::Direction::up:
				GetSprite()->SetRow(11);
				break;
			}
		}
		else
		{
			switch (m_HorizontalDirection)
			{
			case dae::Direction::right:
				GetSprite()->SetRow(2);
				break;
			case dae::Direction::left:
				GetSprite()->SetRow(5);
				break;
			}
		}
	}
	else
	{
		if (m_IsPushing)
		{
			switch (m_IdleDirection)
			{
			case dae::Direction::right:
				GetSprite()->SetRow(3);
				break;
			case dae::Direction::down:
				GetSprite()->SetRow(9);
				break;
			case dae::Direction::left:
				GetSprite()->SetRow(6);
				break;
			case dae::Direction::up:
				GetSprite()->SetRow(12);
				break;
			default:
				break;
			}
		}
		else 
		{
			switch (m_IdleDirection)
			{
			case dae::Direction::right:
				GetSprite()->SetRow(0);
				break;
			case dae::Direction::down:
				GetSprite()->SetRow(7);
				break;
			case dae::Direction::left:
				GetSprite()->SetRow(4);
				break;
			case dae::Direction::up:
				GetSprite()->SetRow(10);
				break;
			default:
				break;
			}
		}
	}
	GetSprite()->Render();
}
