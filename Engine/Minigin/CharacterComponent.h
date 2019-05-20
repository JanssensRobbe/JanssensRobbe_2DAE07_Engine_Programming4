#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "SceneManager.h"
namespace dae
{
	class SpriteComponent;
	class TextureComponent;
	class Command;
	class CharacterComponent : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		void SetDirection(Direction direction)
		{
			if (direction == dae::Direction::none)
				m_UseIdle = true;
			else if (direction == dae::Direction::down || direction == dae::Direction::up)
			{
				m_VerticalDirection = direction;
				m_UseVerticalDirection = true;
				m_UseIdle = false;
				m_IdleDirection = direction;
			}
			else
			{
				m_HorizontalDirection = direction;
				m_UseVerticalDirection = false;
				m_UseIdle = false;
				m_IdleDirection = direction;
			}
		}
		Direction GetDirection()
		{
			if (m_UseVerticalDirection)
				return m_VerticalDirection;
			else
				return m_HorizontalDirection;
		}

		Point2f GetPosition()
		{
			return m_PlayerPos;
		}

		void SetIsDigging(bool IsDigging)
		{
			m_IsDigging = IsDigging;
		}

		bool GetIsDigging()
		{
			return m_IsDigging;
		}

		CharacterComponent(DWORD playerNumber, SpriteComponent& spriteComponent);
		virtual ~CharacterComponent() = default;
		CharacterComponent(const CharacterComponent& other) = delete;
		CharacterComponent(CharacterComponent&& other) = delete;
		CharacterComponent& operator=(const CharacterComponent& other) = delete;
		CharacterComponent& operator=(CharacterComponent&& other) = delete;

	private:
		SpriteComponent* m_pSprite;
		DWORD m_PlayerNumber;
		float m_MovementSpeed, m_DiggingSpeed;
		State m_PlayerState;
		Point2f m_PlayerPos;
		Direction m_HorizontalDirection, m_VerticalDirection, m_IdleDirection;
		bool m_UseVerticalDirection,m_IsDigging, m_UseIdle, m_UseVerticalDirectionSprite;
		std::shared_ptr<Command> m_pCommand;
		Point2f m_XLimits, m_YLimits;
	};
}

