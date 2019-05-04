#include "MiniginPCH.h"
#include "Level.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"


dae::LevelComponent::LevelComponent()
	:m_PlayerPosition{0.0f,0.0f}
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
}

void dae::LevelComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_PlayerPosition = SceneManager::GetInstance().GetActiveScene().GetPlayerPosition();

	for (int i{}; i < m_pTiles.size() - 1; i++)
	{
		if (m_PlayerPosition.x >= m_pTiles[i]->Position.x && m_PlayerPosition.x < m_pTiles[i]->Position.x + 48
			&& m_PlayerPosition.y <= m_pTiles[i]->Position.y && m_PlayerPosition.y > m_pTiles[i]->Position.y - 48)
		{
			if (m_pTiles[i]->tileName != TileName::Black && m_pTiles[i]->tileName != TileName::Sky)
			{
				m_pTiles[i]->tileName = TileName::Black;
			}

			switch (SceneManager::GetInstance().GetActiveScene().GetPlayerDirection())
			{
				case dae::Direction::right:
					if (i + 18 > m_pTiles.size())
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

void dae::LevelComponent::Render()
{
	for (int i{}; i < m_pTiles.size(); i++)
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

	
}

void dae::LevelComponent::SetPlayerPosition(Point2f playerPosition)
{
	m_PlayerPosition.x = playerPosition.x;
	m_PlayerPosition.y = playerPosition.y;
}




