#include "MiniginPCH.h"
#include "Score.h"
#include "ResourceManager.h"

void dae::Score::AddScore(const int playerIndex, Multiplier multiplier)
{
	switch (multiplier)
	{
	case dae::Score::Multiplier::ScoreNormal1:
		m_Score[playerIndex] += 100;
		PrintOutScore(playerIndex);
		break;
	case dae::Score::Multiplier::ScoreNormal2:
		m_Score[playerIndex] += 200;
		PrintOutScore(playerIndex);
		break;
	case dae::Score::Multiplier::ScoreNormal3:
		m_Score[playerIndex] += 400;
		PrintOutScore(playerIndex);
		break;
	case dae::Score::Multiplier::ScoreNormal4:
		m_Score[playerIndex] += 800;
		PrintOutScore(playerIndex);
		break;
	case dae::Score::Multiplier::ScoreRock1:
		m_Score[playerIndex] += 1000;
		PrintOutScore(playerIndex);
		break;
	case dae::Score::Multiplier::ScoreRock2:
		m_Score[playerIndex] += 2000;
		PrintOutScore(playerIndex);
		break;
	case dae::Score::Multiplier::ScoreRock3:
		m_Score[playerIndex] += 4000;
		PrintOutScore(playerIndex);
		break;
	case dae::Score::Multiplier::ScoreRock4:
		m_Score[playerIndex] += 8000;
		PrintOutScore(playerIndex);
		break;
	}

}

void dae::Score::PrintOutScore(int playerIndex)
{
	std::cout << "Player: " << playerIndex << " Has a score of " << m_Score[playerIndex] << std::endl;
}



