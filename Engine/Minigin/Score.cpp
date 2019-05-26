#include "MiniginPCH.h"
#include "Score.h"
#include "ResourceManager.h"

void dae::Score::onNotify(const int playerIndex, Event event)
{
	switch (event)
	{
	case dae::Observer::Event::ScoreNormal1:
		m_Score[playerIndex] += 100;
		PrintOutScore(playerIndex);
		break;
	case dae::Observer::Event::ScoreNormal2:
		m_Score[playerIndex] += 200;
		PrintOutScore(playerIndex);
		break;
	case dae::Observer::Event::ScoreNormal3:
		m_Score[playerIndex] += 400;
		PrintOutScore(playerIndex);
		break;
	case dae::Observer::Event::ScoreNormal4:
		m_Score[playerIndex] += 800;
		PrintOutScore(playerIndex);
		break;
	case dae::Observer::Event::ScoreRock1:
		m_Score[playerIndex] += 1000;
		PrintOutScore(playerIndex);
		break;
	case dae::Observer::Event::ScoreRock2:
		m_Score[playerIndex] += 2000;
		PrintOutScore(playerIndex);
		break;
	case dae::Observer::Event::ScoreRock3:
		m_Score[playerIndex] += 4000;
		PrintOutScore(playerIndex);
		break;
	case dae::Observer::Event::ScoreRock4:
		m_Score[playerIndex] += 8000;
		PrintOutScore(playerIndex);
		break;
	}

}

void dae::Score::PrintOutScore(int playerIndex)
{
	std::cout << "Player: " << playerIndex << " Has a score of " << m_Score[playerIndex] << std::endl;
}



