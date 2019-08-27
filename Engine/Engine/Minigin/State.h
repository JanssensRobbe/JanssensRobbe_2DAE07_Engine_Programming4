#pragma once
#include <vector>

namespace  dae {
	class GameObject;
	class Action;
	class Transition;
	class State final
	{
	public:
		State(std::vector< std::shared_ptr<Action>> actions, std::vector< std::shared_ptr<Action>> entryActions, std::vector< std::shared_ptr<Action>> exitActions, std::vector<std::shared_ptr <Transition>> transitions);
		State() = default;
		~State() = default;

		void SetActions(std::vector< std::shared_ptr<Action>> actions, ActionName actionName);

		void SetAction(std::shared_ptr<Action>action, ActionName actionName);

		void RunAction(int index, ActionName actionName) const;

		void SetTransitions(std::vector<std::shared_ptr<Transition>> transitions);

		void SetTransition(std::shared_ptr<Transition> transition);

		std::vector<std::shared_ptr<Transition>> GetTransition() const { return m_pTransitions; }

	private:
		std::vector<std::shared_ptr<Action>> m_pEntryActions;
		std::vector< std::shared_ptr<Action>> m_pExitActions;
		std::vector< std::shared_ptr<Action>> m_pActions;
		std::vector<std::shared_ptr <Transition>> m_pTransitions;
	};
}

