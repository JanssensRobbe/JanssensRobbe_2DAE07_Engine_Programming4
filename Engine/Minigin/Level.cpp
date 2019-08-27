#include "MiniginPCH.h"
#include "Level.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "./../DigDug/StoneComponent.h"
#include <time.h>
#include "BinReader.h"
#include "Servicelocator.h"


dae::LevelComponent::LevelComponent(std::string levelPath, int playerAmount)
	:m_filePath{levelPath}
	, m_pStoneTexture{ new TextureComponent{"Stone.png"} }
{
	for (int j{}; j < 864; j += 48)
	{
		for (int i{}; i < 672; i += 48)
		{
			if (j < 96)
				m_pTiles.push_back(new Tile{ new TextureComponent{"Ground.png"}, Point2f{ float(i),float(j)}, TileName::Sky });
			else if (j < 288)

				m_pTiles.push_back(new Tile{ new TextureComponent{"Ground.png"}, Point2f{ float(i),float(j)}, TileName::Ground1 });
			else if (j < 480)
				m_pTiles.push_back(new Tile{ new TextureComponent{"Ground.png"}, Point2f{ float(i),float(j)}, TileName::Ground2 });
			else if (j < 672)
				m_pTiles.push_back(new Tile{ new TextureComponent{"Ground.png"}, Point2f{ float(i),float(j)}, TileName::Ground3 });
			else if (j < 816)
				m_pTiles.push_back(new Tile{  new TextureComponent{"Ground.png"}, Point2f{ float(i),float(j)}, TileName::Ground4 });
			else
				m_pTiles.push_back(new Tile{  new TextureComponent{"Ground.png"}, Point2f{ float(i),float(j)}, TileName::Black });
		}
	}
	BinReader Reader{ m_filePath };

	for (unsigned int i{}; i < m_pTiles.size(); i++)
	{
		ServiceLocator::RegisterTile(i, m_pTiles[i]);
		if (Reader.Read<bool>() && m_pTiles[i]->tileName != dae::TileName::Sky)
		{
			m_pTiles[i]->tileName = dae::TileName::Black;
		}
	}
	Reader.CloseFile();

	for (int i{}; i < 4; ++i)
	{
		int row = rand() % 10 + 4;
		int column = rand() % 14;
		m_pStones.push_back(new StoneComponent{ *m_pStoneTexture,column + row * 14 - 1});
	}

	for (int i{}; i < playerAmount; ++i)
	{
		m_PlayerPositions.push_back(Point2f{});
	}
}

void dae::LevelComponent::Update(float deltaTime)
{
	for (unsigned int i{}; i < m_PlayerPositions.size(); ++i)
	{
		m_PlayerPositions[i] = SceneManager::GetInstance().GetCharacter(i)->GetPosition();
	}
	for (unsigned int j{}; j < m_PlayerPositions.size(); ++j)
	{
		//Point2f calPos{ m_PlayerPositions[j].x,m_PlayerPositions[j].y };
		calPos.x = m_PlayerPositions[j].x; 
		calPos.y = m_PlayerPositions[j].y;
		auto playerDir = SceneManager::GetInstance().GetCharacter(j)->GetDirection();
		if (playerDir == dae::Direction::right)
		{
			calPos.x += 40.0f;
			calPos.y += 24.0f;
		}
		else if (playerDir == dae::Direction::left)
		{
			calPos.y += 24.0f;
		}
		else if (playerDir == dae::Direction::down)
		{
			calPos.y += 40.0f;
			calPos.x += 24.0f;
		}
		else if (playerDir == dae::Direction::up)
		{
			calPos.x += 24.0f;
		}
		for (unsigned int i{}; i < m_pTiles.size() - 1; i++)
		{
			if (calPos.x >= m_pTiles[i]->Position.x && calPos.x < m_pTiles[i]->Position.x + 48
				&& calPos.y >= m_pTiles[i]->Position.y && calPos.y < m_pTiles[i]->Position.y + 48)
			{
				if (m_pTiles[i]->tileName != TileName::Black && m_pTiles[i]->tileName != TileName::Sky)
				{
					m_pTiles[i]->tileName = TileName::Black;
				}

				switch (SceneManager::GetInstance().GetCharacter(j)->GetDirection())
				{
				case dae::Direction::right:
					if (i + 1 > int(m_pTiles.size()))
					{
						if (m_pTiles[i]->tileName != TileName::Black && m_pTiles[i]->tileName != TileName::Sky)
							SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(true);
						else
							SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(false);
					}
					else
					{
						if (m_pTiles[i + 1]->tileName != TileName::Black && m_pTiles[i + 1]->tileName != TileName::Sky)
							SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(true);
						else
							SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(false);
					}
					break;
				case dae::Direction::left:
					if (i - 1 < 0)
					{
						if (m_pTiles[i]->tileName != TileName::Black && m_pTiles[i]->tileName != TileName::Sky)
							SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(true);
						else
							SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(false);
					}
					else
					{
						if (m_pTiles[i - 1]->tileName != TileName::Black && m_pTiles[i - 1]->tileName != TileName::Sky)
							SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(true);
						else
							SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(false);
					}
					break;
				case dae::Direction::up:
					if (m_pTiles[i - 14]->tileName != TileName::Black && m_pTiles[i - 14]->tileName != TileName::Sky)
						SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(true);
					else
						SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(false);
					break;
				case dae::Direction::down:
					if (m_pTiles[i + 14]->tileName != TileName::Black)
						SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(true);
					else
						SceneManager::GetInstance().GetCharacter(j)->SetIsDigging(false);
					break;
				}
			}
		}
	}
	for (unsigned int i{}; i < m_pStones.size(); ++i)
	{
		if (m_pStones[i]->GetIsDead())
		{
			delete m_pStones[i];
			m_pStones[i] = m_pStones[m_pStones.size() - 1];
			m_pStones.pop_back();
		}
	}
	for(auto stone : m_pStones)
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
	m_pTiles[0]->Texture->Render(Rectf{ calPos.x,calPos.y,10.0f,10.0f, },Rectf{ 0.0f,0.0f,16.0f,16.0f });

	for (auto stone : m_pStones)
	{
		stone->Render();
	}
}


