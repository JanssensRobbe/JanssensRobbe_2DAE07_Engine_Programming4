#pragma once
#include "CharacterComponent.h"
#include "TextureComponent.h"
namespace dae {
	class HealthComponent;
	class PengoCharacterComponent :public CharacterComponent
	{
	public:
		PengoCharacterComponent(DWORD playerNumber, SpriteComponent& spriteComponent, Point2f respawnPoint, dae::SceneType endscreenType);
		virtual ~PengoCharacterComponent() = default;

		void SetDirection(Direction direction)
		{
			if (direction == dae::Direction::none)
			{
				if (m_UseVerticalDirection)
					m_IdleDirection = m_VerticalDirection;
				else
					m_IdleDirection = m_HorizontalDirection;
				m_UseIdle = true;
			}
				
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
		
		Direction GetIdleDirection() { return m_IdleDirection; }

		void SetIsPushing(bool IsPushing) { m_IsPushing = IsPushing; }
		bool GetIsPushing() { return m_IsPushing; }

		void Reset()
		{
			m_IsDead = false;
			GetTransform()->SetPosition(m_RespawnLocation.x,m_RespawnLocation.y);
			m_HorizontalDirection = Direction::right;
			m_IdleDirection = Direction::right;	
			m_UseIdle = true;
			m_IsPushing = false;
			m_UseVerticalDirection = false;
		}
		virtual void Update(float elapsedTime) override;
		virtual void Render() override;

		PengoCharacterComponent(const PengoCharacterComponent& other) = delete;
		PengoCharacterComponent(PengoCharacterComponent&& other) = delete;
		PengoCharacterComponent& operator=(const PengoCharacterComponent& other) = delete;
		PengoCharacterComponent& operator=(PengoCharacterComponent&& other) = delete;
	private:
		void UpdateArrowCollision();
		void CheckEnemyCollision();
		bool CheckBlockCollsion(float newPos, Direction direction);

		float m_MovementSpeed;
		Point2f m_PlayerPos;
		Direction m_HorizontalDirection, m_VerticalDirection, m_IdleDirection;
		bool m_UseVerticalDirection, m_UseIdle, m_UseVerticalDirectionSprite, m_IsPushing, m_IsDead, m_IsGameOver, m_IsRegistered, m_IsBlockMoving;
		std::shared_ptr<Command> m_pCommand;
		Point2f m_XLimits, m_YLimits;
		int m_CollisionIndex;
		float m_IsDeadTimer;
		Point2f m_RespawnLocation;
		dae::SceneType m_SceneType;
	};
}
