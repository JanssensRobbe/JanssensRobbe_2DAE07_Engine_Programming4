#include "MiniginPCH.h"
#include "StateMachine.h"



dae::StateMachine::StateMachine(EnemyType enemyType)
	: m_EnemyType{enemyType}
	, m_State{State::Wander}
	, m_DetectionRange{40.0f}
{
	
}

void dae::StateMachine::RangeCheck(Point2f pos)
{
		if (pos.x * pos.x + pos.y * pos.y < m_DetectionRange * m_DetectionRange)
		{
			m_State = State::Seek;
		}
}

void dae::StateMachine::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	if(m_State == State::Wander)
	{
		//RangeCheck();
	}


	//CheckHit();
}