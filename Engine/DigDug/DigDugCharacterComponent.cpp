#include "pch.h"
#include "CharacterComponent.h"
#include "DigDugCharacterComponent.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "Level.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Command.h"
#include "ServiceLocator.h"
#include "HealthComponent.h"
#include "GameOverScene.h"
#include "WinnerScene.h"

dae::DigDugCharacterComponent::DigDugCharacterComponent(DWORD playerNumber, SpriteComponent& spriteComponent, Point2f respawnPoint, dae::SceneType endscreenType)
	:CharacterComponent{playerNumber,spriteComponent}
	, m_PlayerPos{ 0.0f,0.0f }
	, m_HorizontalDirection{ dae::Direction::right }
	, m_VerticalDirection{ dae::Direction::down }
	, m_UseVerticalDirection{ false }
	, m_MovementSpeed{ 100.0f }
	, m_DiggingSpeed{ 75.0f }
	, m_Texture{"ArrowRight.png"}
	, m_IsDead{false}
	, m_IsGameOver{false}
	, m_IsRegistered{false}
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
}

void dae::DigDugCharacterComponent::Update(float elapsedTime)
{
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
		
		if (m_SceneType == SceneType::GameOverMenu)
		{
			auto scene = std::make_shared<GameOverScene>("GameOverScene");
			SceneManager::GetInstance().CreateScene(m_SceneType, scene);
			scene->LoadScene();
			SceneManager::GetInstance().SetActiveScene(m_SceneType);
		}
		else if (m_SceneType == SceneType::WinnerMenu)
		{
			auto scene = std::make_shared<WinnerScene>("WinnerScrene");
			SceneManager::GetInstance().CreateScene(m_SceneType, scene);
			scene->LoadScene();
			SceneManager::GetInstance().SetActiveScene(m_SceneType);
		}
		
	}
	UpdateArrowCollision();
	m_PlayerPos = GetTransform()->GetPosition();
	UNREFERENCED_PARAMETER(elapsedTime);
	CheckEnemyCollision();
	CheckStoneCollision();
	m_pCommand = InputManager::GetInstance().handleInput(GamepadIndex(GetPlayerNumber()));
	m_pCommand->execute((*GetGameObject()));
	float newPos{};

	if (m_IsDigging)
		newPos = m_DiggingSpeed * elapsedTime;
	else
		newPos = m_MovementSpeed * elapsedTime;

	if (!m_UseIdle)
	{
		if (m_HorizontalDirection == Direction::right && !m_UseVerticalDirection)
		{
			if (m_PlayerPos.x + newPos < m_XLimits.y
				&& int(m_PlayerPos.y) % 48 == 0) {
				m_UseVerticalDirectionSprite = false;
				GetTransform()->SetPosition(m_PlayerPos.x + newPos, m_PlayerPos.y);
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
				GetTransform()->SetPosition(m_PlayerPos.x - newPos, m_PlayerPos.y);
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
				GetTransform()->SetPosition(m_PlayerPos.x, m_PlayerPos.y - newPos);
				m_UseVerticalDirectionSprite = true;
			}
			else if (m_PlayerPos.y + newPos < m_YLimits.x)
				GetTransform()->SetPosition(m_PlayerPos.x, m_YLimits.x);
			else if (int(m_PlayerPos.x) % 48 != 0)
			{
				m_UseVerticalDirectionSprite = false;
				if (int(m_PlayerPos.x) % 48 <3)
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
				m_UseVerticalDirectionSprite = true;
				GetTransform()->SetPosition(m_PlayerPos.x, m_PlayerPos.y + newPos);
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

void dae::DigDugCharacterComponent::UpdateArrowCollision()
{
	if (!m_IsRegistered)
	{
		m_CollisionIndex = ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->AddCollider(Tag{ "PlayerArrow" }, Rectf{ m_PlayerPos.x + 48.0f,m_PlayerPos.y, 96.0f,48.0f });
		m_IsRegistered = true;
	}
	else if (m_IsPumping)
	{
		ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex, true);
		switch (m_IdleDirection)
		{
		case dae::Direction::right:
			ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollisionIndex, Rectf{ m_PlayerPos.x + 48.0f,m_PlayerPos.y, 96.0f,48.0f });
			break;
		case dae::Direction::down:
			ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollisionIndex, Rectf{ m_PlayerPos.x,m_PlayerPos.y + 48.0f, 48,96.0f });
			break;
		case dae::Direction::left:
			ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollisionIndex, Rectf{ m_PlayerPos.x - 96.0f,m_PlayerPos.y, 96.0f,48.0f });
			break;
		case dae::Direction::up:
			ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollisionIndex, Rectf{ m_PlayerPos.x,m_PlayerPos.y - 96.0f, 48.0f,96.0f });
			break;
		}
	}
	else
	{
		ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex, false);
	}
}

void dae::DigDugCharacterComponent::CheckEnemyCollision()
{
	auto isHit = ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "Enemy" }, Rectf{ m_PlayerPos.x, m_PlayerPos.y,48.0f,48.0f });
	if (isHit && !m_IsDead)
	{
		m_IsDead = true;
		if (GetGameObject()->GetComponent<HealthComponent>()->DecreaseHealth() == 0)
		{
			m_IsGameOver = true;
		}
	}
}

void dae::DigDugCharacterComponent::CheckStoneCollision()
{
	auto isHit = ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->CheckCollision(Tag{ "Stone" }, Rectf{ m_PlayerPos.x, m_PlayerPos.y,48.0f,48.0f });
	if (isHit && !m_IsDead)
	{
		m_IsDead = true;
		if (GetGameObject()->GetComponent<HealthComponent>()->DecreaseHealth() == 0)
		{
			m_IsGameOver = true;
		}
	}
}

void dae::DigDugCharacterComponent::Render()
{
	if (m_IsDead)
	{
		GetSprite()->SetRow(23);
		return;
	}
	if (!m_UseIdle)
	{
		if (m_UseVerticalDirectionSprite)
		{
			switch (m_VerticalDirection)
			{
			case dae::Direction::down:
				if (m_IsDigging)
					GetSprite()->SetRow(17);
				else
					GetSprite()->SetRow(18);
				break;
			case dae::Direction::up:
				if (m_IsDigging)
					GetSprite()->SetRow(14);
				else
					GetSprite()->SetRow(13);
				break;
			}
		}
		else
		{
			switch (m_HorizontalDirection)
			{
			case dae::Direction::right:
				if (m_IsDigging)
					GetSprite()->SetRow(8);
				else
					GetSprite()->SetRow(9);
				break;
			case dae::Direction::left:
				if (m_IsDigging)
					GetSprite()->SetRow(11);
				else
					GetSprite()->SetRow(12);
				break;
			}
		}
	}
	else
	{
		if (m_IsPumping)
		{
			switch (m_IdleDirection)
			{
			case dae::Direction::right:
				GetSprite()->SetRow(7);
				m_Texture.SetTexture("ArrowRight.png");
				m_Texture.Render(Rectf{ m_PlayerPos.x + 48.0f,m_PlayerPos.y, 96.0f,48.0f }, Rectf{ 0.0f,0.0f, 96.0f,48.0f });
				break;
			case dae::Direction::down:
				GetSprite()->SetRow(16);
				m_Texture.SetTexture("ArrowDown.png");
				m_Texture.Render(Rectf{ m_PlayerPos.x,m_PlayerPos.y + 48.0f, 48,96.0f }, Rectf{ 0.0f,0.0f, 48.0f,96.0f });
				break;
			case dae::Direction::left:
				GetSprite()->SetRow(10);
				m_Texture.SetTexture("ArrowLeft.png");
				m_Texture.Render(Rectf{ m_PlayerPos.x - 96.0f,m_PlayerPos.y, 96.0f,48.0f }, Rectf{ 0.0f,0.0f, 96.0f,48.0f });
				break;
			case dae::Direction::up:
				GetSprite()->SetRow(15);
				m_Texture.SetTexture("ArrowUp.png");
				m_Texture.Render(Rectf{ m_PlayerPos.x,m_PlayerPos.y - 96.0f, 48.0f,96.0f }, Rectf{ 0.0f,0.0f, 48.0f,96.0f });
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
				GetSprite()->SetRow(19);
				break;
			case dae::Direction::down:
				GetSprite()->SetRow(22);
				break;
			case dae::Direction::left:
				GetSprite()->SetRow(20);
				break;
			case dae::Direction::up:
				GetSprite()->SetRow(21);
				break;
			default:
				break;

			}
		}
	}
	GetSprite()->Render();
}
