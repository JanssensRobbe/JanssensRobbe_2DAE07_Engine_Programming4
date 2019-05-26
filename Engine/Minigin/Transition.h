#pragma once

namespace dae {
	class GameObject;
	class State;
	class Condition;
	class Transition final
	{
	public:
		Transition(std::shared_ptr<Condition> conditions, State* nextState);
		Transition() = default;
		~Transition() = default;

		bool Istriggered(int index) const;

		void SetNextState(State* nextState) { m_pNextState = nextState; }

		void SetConditions(std::vector<std::shared_ptr<Condition>> conditions);
		void SetCondition(std::shared_ptr<Condition> condition);

		State* GetNextState() const { return m_pNextState; }
	private:
		State* m_pNextState;
		std::vector<std::shared_ptr<Condition>> m_pConditions;
	};
}

