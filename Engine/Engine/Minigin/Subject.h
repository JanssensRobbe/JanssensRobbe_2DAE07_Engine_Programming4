#pragma once
#include <iostream>
#include "Observer.h"
#include <iostream>
#include <string>

namespace dae {
	class Subject
	{
	public:
		enum class Event {
			EnemyX1 = 0,
			EnemyX2,
			EnemyNest,
			Nest,
			Bonus
		};

		Subject() = default;
		~Subject() = default;
		//register Observers
		void Attach(Observer* obs)
		{
			m_pObservers.push_back(obs);
		}

		//this is the event
		void SetScoreChanged(bool state)
		{
			m_ScoreChanged = state;
			Notify();
		}

		bool GetScoreChanged()
		{
			return m_ScoreChanged;
		}

		void Notify()
		{
			for (auto observer : m_pObservers)
			{
				observer->Notify();
			}
			m_ScoreChanged = false;
		}

		Event GetEvent() {
			return m_Event;
		}

		void SetEvent(Event event) {
			m_Event = event;
		}

		void AddScore(int score)
		{
			m_Score += score;
		}

		int GetScore() { return m_Score; }
		std::string GetScoreString(){ return std::string{ "Your Score: " + std::to_string(m_Score) }; }
	private:
		std::vector<Observer*> m_pObservers;
		bool m_ScoreChanged = false;
		Event m_Event;
		int m_Score;
	};
}

