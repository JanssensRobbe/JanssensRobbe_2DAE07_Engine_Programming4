#pragma once
#include "BaseComponent.h"
#include "structs.h"
#include <map>

namespace dae
{
	class TextureComponent;
	class MovableWallComponent :public BaseComponent
	{
	public:

		MovableWallComponent(std::string nameTexture, int index, bool isEnemyTile = false);
		~MovableWallComponent();
		MovableWallComponent(const MovableWallComponent& other) = delete;
		MovableWallComponent(MovableWallComponent&& other) noexcept = delete;
		MovableWallComponent& operator=(const MovableWallComponent& other) = delete;
		MovableWallComponent& operator=(MovableWallComponent&& other) noexcept = delete;

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		bool GetIsDead() { return m_IsDead;}
		bool GetIsMoving() { return m_isMoving; }
		float GetMovingSpeed() { return m_MovementSpeed; }
		int GetIndex() { return m_Index; }
		Direction GetMovingDirection(){ return m_MovingDirection; }

		void SetBonusBlock() 
		{ 
			m_IsBonusTile = true;
			m_IsEnemyTile = false;
		}

		void SetSpecialActive()
		{
			m_IsSpecialActive = true;
			m_SpecialTimer = m_SpecialDuration;
		}
		bool GetBonusBlock() { return m_IsBonusTile; }
		bool GetEnemyTile() { return m_IsEnemyTile; }

		void EnableMoving(Direction direction) { m_MovingDirection = direction; }

		Point2f GetSpawnEggLocation();
		void DeleteWall();
	private:
		float m_ShowEggTimer = 2.0f;
		Point2f m_Position;
		TextureComponent* m_pTexture;
		bool m_isMoving, m_MayDestroy, m_IsRegistered, m_IsDead, m_StartTimer, m_IsSideChecked, m_IsDisabled, m_IsEnemyTile, m_IsBonusTile, m_IsSpecialActive, m_IsBonusScoreAdded;
		Direction m_MovingDirection;
		int m_Index, m_CollisionIndex, m_MovingStoneIndex;
		float m_MovementSpeed, m_TimerBeforeFall;
		float m_SpecialTimer = 0.0f
			, m_SpecialDuration = 5.0f;
		std::map<int,std::shared_ptr<GameObject>> m_pPlayers;
		Rectf m_Boundries = Rectf{ 0.0f,48.0f, 672.0f, 768.0f };
	};
}

