#pragma once
#include "structs.h"

namespace dae
{
	class StateMachine
	{
		enum class EnemyType {
			Fygar,
			Pooka
		};

		enum class State {
			Wander,
			Seek,
			Damaged,
			Death,
			Fire,
			Ghost
		};

	public:
		StateMachine(EnemyType enemyType);
		~StateMachine() = default;

		void RangeCheck(Point2f pos);
		void Update(float elapsedTime);

	private:
		EnemyType m_EnemyType;
		State m_State;
		float m_DetectionRange;
	};
}

