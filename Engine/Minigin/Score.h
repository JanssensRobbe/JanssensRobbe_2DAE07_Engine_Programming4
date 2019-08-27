#pragma once
#include "Observer.h"
#include <map>
#include "TextComponent.h"


namespace dae
{
	class Score :public Singleton<Score>
	{
	public:
		enum class Multiplier
		{
			ScoreNormal1,
			ScoreNormal2,
			ScoreNormal3,
			ScoreNormal4,
			ScoreRock1,
			ScoreRock2,
			ScoreRock3,
			ScoreRock4
		};
		Score() = default;
		virtual ~Score()
		{
			delete m_Text;
		}
		void Init()
		{
			m_Score.insert({ 0,0 });
			m_Score.insert({ 1,0 });
			m_Score.insert({ 2,0 });
			m_Score.insert({ 3,0 });
		}

		void AddScore(const int playerIndex, Multiplier multiplier);

	private:
		void PrintOutScore(int playerIndex);

		std::map<int,int> m_Score;
		TextComponent* m_Text;
	};

}
