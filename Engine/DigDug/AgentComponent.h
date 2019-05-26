#pragma once
#include "BaseComponent.h"
#include "StateMachine.h"
#include "Score.h"

namespace dae
{
	class AgentComponent :public BaseComponent
	{
	public:
		AgentComponent(int maxNumberInflate, int gridSize, int nbColumns, dae::EnemyType enemyType);
		AgentComponent() = default;
		~AgentComponent();

		void Update(float deltaTime) override;
		void Render() override;
		void Initialize();

		void Walk();
		int calculateIndex() const;
		int GetClosestPlayerTileIndex() const;
		int GetClosestPlayerIndex() const;
		float GetClosestPlayerDistance() const;
		void Collision();
		void RockCollision();
		void Inflate();
		void Dead();
		void DisableCollision() const;
		//int GetScore() const;

		static int GetCount() { return m_Count; }
		static void ResetCount() { m_Count = 0; }

		bool m_IsInvis = false;
		bool m_WasInvis = false;
		bool m_IsBeingInflated = false;
		bool m_WasBeingInflated = false;
		bool m_IsHitByFallingRock = false;
		bool m_IsIdle = true;
		bool m_IsDead = false;

		int m_InflateStatus = 0;
	private:
		float m_ElapsedTime = 0.0f;
		int m_MaxInflate = 0;
		int m_GridSize = 0;
		int m_NumberOfColumns = 0;
		StateMachine* m_pStateMachine = nullptr;
		bool m_Init = false;
		static int m_Count;
		float m_DeflateTime = 0.5f;
		float m_CurrentDeflateTime = 0.0f;
		bool m_Collision = false;
		bool m_HasInflationChanged = false;
		float m_DeadTime = 1.0f;
		float m_CurrentInflateTime = 0.0f;
		bool m_IsActive = true;
		int m_thisInstance = 0;
		float m_InitIdleTime = 1.0f;
		bool m_IsRegistered = false;
		int m_CollsionIndex = 0;
		EnemyType m_EnemyType;
		Direction m_Direction = Direction::right;
		float m_MovementSpeed = 50.0f;
		int m_TileIndex = 0;
		Point2f m_XLimits = Point2f{ 0.0f,0.0f };
		Point2f m_YLimits = Point2f{ 0.0f,0.0f };
		std::shared_ptr<Score> m_pScore;

		//Fygar
		float m_ShootCoolDown = 3.0f;
		float m_ShootCurrentTime = 0.0f;
		float m_ShootDuration = 1.0f;
		bool m_IsShooting = false;
		TextureComponent* m_pShootTexture;

	};
}

