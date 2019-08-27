#include "MiniginPCH.h"
#include "Transition.h"
#include "Condition.h"
#include "State.h"
#include <vector>

///////////////////////////////////////////////////////////////////////////////
// The Whole stateMachine is inspired by the EliteEngine::FiniteStateMachine //
// From GamePlay Programming                                                 //
// So Credits to GamePlay Programming FiniteStateMachine                     //
///////////////////////////////////////////////////////////////////////////////

dae::Transition::Transition(std::shared_ptr<Condition> conditions, State* nextState)
	:m_pNextState(nextState)
{
	m_pConditions.push_back(conditions);
}

bool dae::Transition::Istriggered(int index) const
{
	for (auto condition : m_pConditions)
	{
		if (condition->IsTriggered(index))
			return true;
	}
	return false;
}

void dae::Transition::SetConditions(std::vector<std::shared_ptr<Condition>> conditions)
{
	for (auto condition : conditions)
	{
		if (std::find(m_pConditions.begin(), m_pConditions.end(), condition) == m_pConditions.end())
			m_pConditions.push_back(condition);	
	}
}

void dae::Transition::SetCondition(std::shared_ptr<Condition> condition)
{
	if (std::find(m_pConditions.begin(), m_pConditions.end(), condition) == m_pConditions.end())
		m_pConditions.push_back(condition);
}
