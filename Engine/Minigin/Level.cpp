#include "MiniginPCH.h"
#include "Level.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "./../DigDug/StoneComponent.h"
#include <time.h>


dae::LevelComponent::LevelComponent()
	:m_PlayerPositions{}
{
	for (int i{}; i < 672; i += 48)
	{
		for (int j{}; j < 864; j += 48)
		{		
			if(j < 96)
				m_pTiles.push_back(new Tile{ new TextureComponent{ "Ground.png" }, Point2f{ float(i),float(j)}, TileName::Sky});
			else if (j < 288)
				m_pTiles.push_back(new Tile{ new TextureComponent{ "Ground.png" }, Point2f{ float(i),float(j)}, TileName::Ground1 });
			else if (j < 480)
				m_pTiles.push_back(new Tile{ new TextureComponent{ "Ground.png" }, Point2f{ float(i),float(j)}, TileName::Ground2 });
			else if (j < 672)
				m_pTiles.push_back(new Tile{ new TextureComponent{ "Ground.png" }, Point2f{ float(i),float(j)}, TileName::Ground3 });
			else if (j < 816)
				m_pTiles.push_back(new Tile{ new TextureComponent{ "Ground.png" }, Point2f{ float(i),float(j)}, TileName::Ground4 });
			else
				m_pTiles.push_back(new Tile{ new TextureComponent{ "Ground.png" }, Point2f{ float(i),float(j)}, TileName::Black});
		}
	}
	for (int i{}; i < 4; ++i)
	{
		int row = rand() % 10 + 4;
		int column = rand() % 14;
		m_pStones.push_back(new StoneComponent{ new TextureComponent{"Stone.png"},column * 18 + row - 1,m_pTiles });
	}
}

void dae::LevelComponent::Update(float deltaTime)
{
	m_PlayerPositions = SceneManager::GetInstance().GetActiveScene()->GetPlayerPositions();

	for (unsigned int j{}; j < m_PlayerPositions.size(); j++)
	{
		for (unsigned int i{}; i < m_pTiles.size() - 1; i++)
		{
			if (m_PlayerPositions[j].x >= m_pTiles[i]->Position.x && m_PlayerPositions[j].x < m_pTiles[i]->Position.x + 48
				&& m_PlayerPositions[j].y <= m_pTiles[i]->Position.y && m_PlayerPositions[j].y > m_pTiles[i]->Position.y - 48)
			{
				if (m_pTiles[i]->tileName != TileName::Black && m_pTiles[i]->tileName != TileName::Sky)
				{
					m_pTiles[i]->tileName = TileName::Black;
				}

				switch (SceneManager::GetInstance().GetActiveScene()->GetPlayerDirection())
				{
				case dae::Direction::right:
					if (i + 18 > int(m_pTiles.size()))
					{
						if (m_pTiles[i]->tileName != TileName::Black && m_pTiles[i]->tileName != TileName::Sky)
							InputManager::GetInstance().SetIsDigging(true);
						else
							InputManager::GetInstance().SetIsDigging(false);
					}
					else
					{
						if (m_pTiles[i + 18]->tileName != TileName::Black && m_pTiles[i]->tileName != TileName::Sky)

							InputManager::GetInstance().SetIsDigging(true);
						else
							InputManager::GetInstance().SetIsDigging(false);
					}
					break;
				case dae::Direction::left:
					if (i - 18 < 0)
					{
						if (m_pTiles[i]->tileName != TileName::Black && m_pTiles[i]->tileName != TileName::Sky)
							InputManager::GetInstance().SetIsDigging(true);
						else
							InputManager::GetInstance().SetIsDigging(false);
					}
					else
					{
						if (m_pTiles[i - 18]->tileName != TileName::Black && m_pTiles[i - 18]->tileName != TileName::Sky)

							InputManager::GetInstance().SetIsDigging(true);
						else
							InputManager::GetInstance().SetIsDigging(false);
					}
					break;
				case dae::Direction::up:
					if (m_pTiles[i - 1]->tileName != TileName::Black && m_pTiles[i - 1]->tileName != TileName::Sky)
						InputManager::GetInstance().SetIsDigging(true);
					else
						InputManager::GetInstance().SetIsDigging(false);
					break;
				case dae::Direction::down:
					if (m_pTiles[i + 1]->tileName != TileName::Black)
						InputManager::GetInstance().SetIsDigging(true);
					else
						InputManager::GetInstance().SetIsDigging(false);
					break;
				}
			}
		}
	}

	for (auto stone : m_pStones)
	{
		stone->Update(deltaTime);
	}
}

void dae::LevelComponent::Render()
{
	for (unsigned int i{}; i < m_pTiles.size(); i++)
	{
		if (m_pTiles[i]->tileName == TileName::Sky)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{64.0f,0.0f,16.0f,16.0f});
		}
		else if (m_pTiles[i]->tileName == TileName::Ground1)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{ 48.0f,0.0f,16.0f,16.0f });
		}
		else if (m_pTiles[i]->tileName == TileName::Ground2)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{ 32.0f,0.0f,16.0f,16.0f });
		}
		else if (m_pTiles[i]->tileName == TileName::Ground3)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{ 16.0f,0.0f,16.0f,16.0f });
		}
		else if (m_pTiles[i]->tileName == TileName::Ground4)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{ 0.0f,0.0f,16.0f,16.0f });
		}
		else if (m_pTiles[i]->tileName == TileName::Black)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{ 80.0f,0.0f,16.0f,16.0f });
		}

	}

	for (auto stone : m_pStones)
	{
		stone->Render();
	}

	
}


