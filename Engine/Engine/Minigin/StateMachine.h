#pragma once
#include "structs.h"

namespace dae
{
	class State;
	class GameObject;
	class StateMachine final
	{
	public:
		StateMachine(std::vector<State*> states, State* StartState, int index);
		StateMachine() = default;
		~StateMachine();

		void Update(float deltaTime);

	private:
		std::vector<State*> m_pStates;
		State* m_pState;
		int m_AgentIndex;
	};
}

