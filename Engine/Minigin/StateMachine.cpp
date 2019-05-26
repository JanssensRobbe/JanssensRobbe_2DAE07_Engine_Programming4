#include "MiniginPCH.h"
#include "StateMachine.h"
#include "State.h"
#include "Transition.h"

///////////////////////////////////////////////////////////////////////////////
// The Whole stateMachine is inspired by the EliteEngine::FiniteStateMachine //
// From GamePlay Programming                                                 //
// So Credits to GamePlay Programming FiniteStateMachine                     //
///////////////////////////////////////////////////////////////////////////////

dae::StateMachine::StateMachine(std::vector<State*> states, State* StartState, int index)
	: m_pStates{states}
	, m_pState{StartState}
	, m_AgentIndex{index}
{
	
}

dae::StateMachine::~StateMachine()
{
	delete m_pState;
	for (auto state: m_pStates)
	{
		delete state;
	}
}

void dae::StateMachine::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	auto transitions = m_pState->GetTransition();
	auto isTriggered = false;
	std::shared_ptr<Transition> pTransition = std::make_shared<Transition>();

	for (auto transition : transitions)
	{
		if (transition->Istriggered(m_AgentIndex))
		{
			isTriggered = true;
			pTransition = transition;
			break;
		}
	}

	if (isTriggered)
	{
		const auto nextState = pTransition->GetNextState();

		m_pState->RunAction(m_AgentIndex, dae::ActionName::ExitAction);
		nextState->RunAction(m_AgentIndex, dae::ActionName::EntryAction);
		m_pState = nextState;
	}
	else
		m_pState->RunAction(m_AgentIndex, dae::ActionName::Action);

}
