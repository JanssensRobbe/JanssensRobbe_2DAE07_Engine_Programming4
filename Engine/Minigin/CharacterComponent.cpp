#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "Level.h"
#include "SceneManager.h"
#include "Scene.h"


dae::CharacterComponent::CharacterComponent(int playerNumber, SpriteComponent& spriteComponent)
	:BaseComponent{}
	, m_PlayerNumber{playerNumber}
	, m_HorizontalDirection{Direction::right}
	, m_VerticalDirection{Direction::up}
	, m_pSprite{&spriteComponent}
	, m_PlayerState{dae::State::Idle}
	, m_PlayerPos{0.0f,0.0f}
	, m_UsePreviousDirection{false}
{
}


void dae::CharacterComponent::Update(float elapsedTime)
{
	m_PlayerPos = GetTransform()->GetPosition();
	UNREFERENCED_PARAMETER(elapsedTime);
	m_pCommand = InputManager::GetInstance().handleInput();
	auto direction = m_pCommand->getPlayerDirection();
	if (direction == Direction::up || direction == Direction::down)
	{
		m_VerticalDirection = direction;
		m_pCommand->SetPreviousDirection(m_HorizontalDirection);
	}
	else
	{
		m_HorizontalDirection = direction;
		m_pCommand->SetPreviousDirection(m_VerticalDirection);
	}

	m_PlayerState = m_pCommand->GetPlayerState();
	if(m_PlayerState != dae::State::Idle || m_PlayerState != dae::State::Pumping)
		SceneManager::GetInstance().GetActiveScene()->SetPlayerDirection(direction);
	m_pCommand->execute(GetTransform(), elapsedTime);
	m_UsePreviousDirection = m_pCommand->GetUsePrevious();

	if (m_PlayerState == dae::State::Idle || m_PlayerState == dae::State::Pumping)
	{
		SceneManager::GetInstance().GetActiveScene()->SetPlayerPosition(Point2f(m_PlayerPos.x + 24.0f,m_PlayerPos.y - 24.0f));
	}
	else
	{
		switch (direction)
		{
		case dae::Direction::right:
			SceneManager::GetInstance().GetActiveScene()->SetPlayerPosition(Point2f(m_PlayerPos.x + 24.0f, m_PlayerPos.y - 24.0f));
			break;
		case dae::Direction::left:
			SceneManager::GetInstance().GetActiveScene()->SetPlayerPosition(Point2f(m_PlayerPos.x + 24.0f, m_PlayerPos.y - 24.0f));
			break;
		case dae::Direction::up:
			SceneManager::GetInstance().GetActiveScene()->SetPlayerPosition(Point2f(m_PlayerPos.x + 24.0f, m_PlayerPos.y - 24.0f));
			break;
		case dae::Direction::down:
			SceneManager::GetInstance().GetActiveScene()->SetPlayerPosition(Point2f(m_PlayerPos.x + 24.0f, m_PlayerPos.y - 24.0f));
			break;
		}
	}
}

void dae::CharacterComponent::Render()
{
	m_pCommand->render(m_pSprite,m_UsePreviousDirection);
}