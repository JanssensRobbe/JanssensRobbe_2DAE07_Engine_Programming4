#pragma once
#include "Observer.h"
#include "Subject.h"

namespace dae {
	class ScoreObserver final: public Observer
	{
	public:

		ScoreObserver(Subject* mod)
			:Observer{mod}
		{
		}

		void Notify() override
		{
			if (GetSubject()->GetScoreChanged())
			{
				switch (GetSubject()->GetEvent())
				{
				case Subject::Event::EnemyX1:
					GetSubject()->AddScore(100);
					break;
				case Subject::Event::EnemyX2:
					GetSubject()->AddScore(200);
					break;
				case Subject::Event::EnemyNest:
					GetSubject()->AddScore(500);
					break;
				case Subject::Event::Nest:
					GetSubject()->AddScore(1000);
					break;
				case Subject::Event::Bonus:
					GetSubject()->AddScore(3200);
					break;
				default:
					break;
				}
			}
		};
	private:
	};
}