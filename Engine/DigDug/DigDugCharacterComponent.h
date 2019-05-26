#pragma once
#include "CharacterComponent.h"
#include "TextureComponent.h"
namespace dae {
	class DigDugCharacterComponent :public CharacterComponent
	{
	public:
		DigDugCharacterComponent(DWORD playerNumber, SpriteComponent& spriteComponent, Point2f respawnPoint, dae::SceneType endscreenType);
		virtual ~DigDugCharacterComponent() = default;

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

		virtual Direction GetDirection() override
		{
			if (m_UseVerticalDirection)
				return m_VerticalDirection;
			else
				return m_HorizontalDirection;
		}

		virtual Point2f GetPosition() override
		{
			return m_PlayerPos;
		}

		virtual void SetIsDigging(bool IsDigging) override
		{
			m_IsDigging = IsDigging;
		}
		
		void SetIsPumping(bool IsPumping) { m_IsPumping = IsPumping; }

		bool GetIsDigging()
		{
			return m_IsDigging;
		}
		void Reset()
		{
			m_IsDead = false;
			GetTransform()->SetPosition(336, 432);
			m_HorizontalDirection = Direction::right;
			m_IdleDirection = Direction::right;
			m_IsDigging = false;
			m_UseIdle = true;
			m_IsPumping = false;
			m_UseVerticalDirection = false;
		}
		virtual void Update(float elapsedTime) override;
		virtual void Render() override;

		DigDugCharacterComponent(const DigDugCharacterComponent& other) = delete;
		DigDugCharacterComponent(DigDugCharacterComponent&& other) = delete;
		DigDugCharacterComponent& operator=(const DigDugCharacterComponent& other) = delete;
		DigDugCharacterComponent& operator=(DigDugCharacterComponent&& other) = delete;
	private:
		void UpdateArrowCollision();
		void CheckEnemyCollision();
		void CheckStoneCollision();

		float m_MovementSpeed, m_DiggingSpeed;
		Point2f m_PlayerPos;
		Direction m_HorizontalDirection, m_VerticalDirection, m_IdleDirection;
		bool m_UseVerticalDirection, m_IsDigging, m_UseIdle, m_UseVerticalDirectionSprite, m_IsPumping, m_IsDead, m_IsGameOver, m_IsRegistered;
		std::shared_ptr<Command> m_pCommand;
		Point2f m_XLimits, m_YLimits;
		TextureComponent m_Texture;
		int m_CollisionIndex;
		float m_IsDeadTimer;
		Point2f m_RespawnLocation;
		dae::SceneType m_SceneType;
	};
}
