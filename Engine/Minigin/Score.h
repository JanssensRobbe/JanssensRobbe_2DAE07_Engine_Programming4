#pragma once
#include "Observer.h"
#include <map>
#include "TextComponent.h"


namespace dae
{
	class Score :public Observer
	{
	public:
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
		virtual void onNotify(const int playerIndex, Event event) override;

	private:
		void PrintOutScore(int playerIndex);

		std::map<int,int> m_Score;
		TextComponent* m_Text;
	};

}
