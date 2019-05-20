#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "Level.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Command.h"



dae::CharacterComponent::CharacterComponent(DWORD playerNumber, SpriteComponent& spriteComponent)
	:BaseComponent{}
	, m_PlayerNumber{playerNumber}
	, m_pSprite{&spriteComponent}
	, m_PlayerState{dae::State::Idle}
	, m_PlayerPos{0.0f,0.0f}
	, m_HorizontalDirection{dae::Direction::right}
	, m_VerticalDirection{ dae::Direction::down}
	, m_UseVerticalDirection{false}
	, m_MovementSpeed{100.0f}
	, m_DiggingSpeed{75.0f}
	, m_XLimits{ 0,624 }
	, m_YLimits{ 48,768 }
{
}


void dae::CharacterComponent::Update(float elapsedTime)
{
	m_PlayerPos = GetTransform()->GetPosition();
	UNREFERENCED_PARAMETER(elapsedTime);
	m_pCommand = InputManager::GetInstance().handleInput(GamepadIndex(m_PlayerNumber));
	if (m_pCommand != std::shared_ptr<NullCommand>())
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
					if (int(m_PlayerPos.y) % 48 < 1)
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
					if (int(m_PlayerPos.y) % 48 < 1)
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
					if (int(m_PlayerPos.x) % 48 < 1)
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
					if (int(m_PlayerPos.x) % 48 < 1)
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

void dae::CharacterComponent::Render()
{
	if (!m_UseIdle)
	{
		if (m_UseVerticalDirectionSprite)
		{
			switch (m_VerticalDirection)
			{
			case dae::Direction::down:
				if (m_IsDigging)
					m_pSprite->SetRow(17);
				else
					m_pSprite->SetRow(18);
				break;
			case dae::Direction::up:
				if (m_IsDigging)
					m_pSprite->SetRow(14);
				else
					m_pSprite->SetRow(13);
				break;
			}
		}
		else
		{
			switch (m_HorizontalDirection)
			{
			case dae::Direction::right:
				if (m_IsDigging)
					m_pSprite->SetRow(8);
				else
					m_pSprite->SetRow(9);
				break;
			case dae::Direction::left:
				if (m_IsDigging)
					m_pSprite->SetRow(11);
				else
					m_pSprite->SetRow(12);
				break;
			}
		}
	}
	else
	{

		switch (m_IdleDirection)
		{
		case dae::Direction::right:
			m_pSprite->SetRow(19);
			break;
		case dae::Direction::down:
			m_pSprite->SetRow(18);
			break;
		case dae::Direction::left:
			m_pSprite->SetRow(20);
			break;
		case dae::Direction::up:
			m_pSprite->SetRow(21);
			break;
		default:
			break;

		}
		m_pSprite->Render();
	}
}