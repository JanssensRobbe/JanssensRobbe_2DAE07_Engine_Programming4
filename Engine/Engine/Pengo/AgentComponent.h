#pragma once
#include "BaseComponent.h"
#include "StateMachine.h"
#include "Score.h"

namespace dae
{
	class AgentComponent :public BaseComponent
	{
	public:
		AgentComponent(int gridSize, int nbColumns, dae::EnemyType enemyType,bool isInvisible = false);
		AgentComponent() = default;
		~AgentComponent()
		{
			delete m_pStateMachine;
		}

		void Update(float deltaTime) override;
		void Render() override;
		void Initialize();

		void Walk();
		void GetClosestPlayer();
		int calculateIndex() const;
		int GetClosestPlayerTileIndex() const;
		int GetClosestPlayerIndex() const;
		float GetClosestPlayerDistance() const;
		void Collision();
		void Dead();
		void FollowRock();
		void Stun();
		void DisableCollision() const;
		void SetInvisible(bool state) { m_IsInvisible = state; }
		static int GetCount() { return m_Count; }
		static void ResetCount() { m_Count = 0; }
		bool m_IsInvis = false;
		bool m_IsStunned = false;
		bool m_WasInvis = false;
		bool m_IsHitByFlyingRock = false;
		bool m_IsIdle = true;
		bool m_IsDead = false;
		bool m_ChasePlayer = false;
	private:
		float m_ElapsedTime = 0.0f;
		int m_GridSize = 48;
		int m_NumberOfColumns = 14;
		bool m_ChosenDirection = false;
		bool m_IsInGrid = false;
		StateMachine* m_pStateMachine = nullptr;
		bool m_Init = false;
		static int m_Count;
		bool m_Collision = false;
		float m_DeadTime = 1.0f;
		float m_CurrentInflateTime = 0.0f;
		bool m_IsActive = true;
		float m_InitIdleTime = 2.0f;
		float m_InitIdleMax = 2.0f;
		bool m_IsRegistered = false;
		bool m_IsInvisible;
		int m_CollsionIndex = 0;
		int m_MovingWallIndex = 0;
		int m_Index = 0;
		EnemyType m_EnemyType;
		Direction m_Direction = Direction::right;
		Direction m_HitDirection = Direction::none;
		float m_MovementSpeed = 50.0f;
		float m_RunningSpeed = 100.0f;
		bool m_UseRunningSpeed = false;
		float m_RunningSpeedTimer = 30.0f;
		int m_TileIndex = 0;
		Point2f m_XLimits = Point2f{ 0.0f,0.0f };
		Point2f m_YLimits = Point2f{ 0.0f,0.0f };
	};
}

