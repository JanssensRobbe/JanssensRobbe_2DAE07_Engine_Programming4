#include "MiniginPCH.h"
#include "State.h"
#include "Action.h"
#include "Transition.h"

///////////////////////////////////////////////////////////////////////////////
// The Whole stateMachine is inspired by the EliteEngine::FiniteStateMachine //
// From GamePlay Programming                                                 //
// So Credits to GamePlay Programming FiniteStateMachine                     //
///////////////////////////////////////////////////////////////////////////////

dae::State::State(std::vector< std::shared_ptr<Action>> actions, std::vector< std::shared_ptr<Action>> entryActions, std::vector<std::shared_ptr<Action>> exitActions, std::vector<std::shared_ptr <Transition>> transitions)
	:m_pEntryActions{entryActions}
	,m_pActions{actions}
	, m_pExitActions{exitActions}
{
}

void dae::State::SetActions(std::vector< std::shared_ptr<Action>> actions, ActionName actionName)
{
	for (int i{}; i < actions.size(); i++)
	{
		switch (actionName)
		{
		case dae::ActionName::Action:
			if (std::find(m_pActions.begin(), m_pActions.end(), actions[i]) == m_pActions.end())
				m_pActions.push_back(actions[i]);
				break;
		case dae::ActionName::EntryAction:
			if (std::find(m_pEntryActions.begin(), m_pEntryActions.end(), actions[i]) == m_pEntryActions.end())
				m_pEntryActions.push_back(actions[i]);
			break;
		case dae::ActionName::ExitAction:
			if (std::find(m_pExitActions.begin(), m_pExitActions.end(), actions[i]) == m_pExitActions.end())
				m_pExitActions.push_back(actions[i]);
			break;
		}
	}
}

void dae::State::SetAction(std::shared_ptr<Action> action, ActionName actionName)
{
	switch (actionName)
	{
	case dae::ActionName::Action:
		if (std::find(m_pActions.begin(), m_pActions.end(), action) == m_pActions.end())
			m_pActions.push_back(action);
		break;
	case dae::ActionName::EntryAction:
		if (std::find(m_pEntryActions.begin(), m_pEntryActions.end(), action) == m_pEntryActions.end())
			m_pEntryActions.push_back(action);
		break;
	case dae::ActionName::ExitAction:
		if (std::find(m_pExitActions.begin(), m_pExitActions.end(), action) == m_pExitActions.end())
			m_pExitActions.push_back(action);
		break;
	}
}

void dae::State::SetTransitions(std::vector<std::shared_ptr<Transition>> transitions)
{
	for (int i{}; i < transitions.size(); i++)
	{
		if (std::find(m_pTransitions.begin(), m_pTransitions.end(), transitions[i]) == m_pTransitions.end())
			m_pTransitions.push_back(transitions[i]);
	}
}

void dae::State::SetTransition(std::shared_ptr<Transition> transition)
{
	if (std::find(m_pTransitions.begin(), m_pTransitions.end(), transition) == m_pTransitions.end())
		m_pTransitions.push_back(transition);
}

void dae::State::RunAction(int index, ActionName actionName) const
{
	switch (actionName)
	{
	case dae::ActionName::Action:
		for (auto action : m_pActions)
		{
			action->Invoke(index);
		}
		break;
	case dae::ActionName::EntryAction:
		for (auto action : m_pEntryActions)
		{
			action->Invoke(index);
		}
		break;
	case dae::ActionName::ExitAction:
		for (auto action : m_pExitActions)
		{
			action->Invoke(index);
		}
		break;
	}
}
