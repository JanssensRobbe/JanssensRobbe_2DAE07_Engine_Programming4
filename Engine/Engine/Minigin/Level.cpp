#include "MiniginPCH.h"
#include "Level.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "./../Pengo/MovableWallComponent.h"
#include <time.h>
#include "BinReader.h"
#include "locator.h"
#include "CollisionComponent.h"
#include "./../Pengo/AgentComponent.h"


dae::LevelComponent::LevelComponent(std::string levelPath, int playerAmount)
	:m_filePath{ levelPath }
{
	for (int j{}; j < 864; j += 48)
	{
		for (int i{}; i < 672; i += 48)
		{
			if (j < 48 || j >= 816)
			{
				m_pTiles.push_back(new Tile{ new TextureComponent{"tiles.png"}, Point2f{ float(i),float(j)}, TileName::Border });
			}
			else
			{
				m_pTiles.push_back(new Tile{ new TextureComponent{"tiles.png"}, Point2f{ float(i),float(j)}, TileName::Black });
			}
		}
	}
	BinReader Reader{ m_filePath };

	for (unsigned int i{}; i < m_pTiles.size(); i++)
	{
		Locator::RegisterTile(i, m_pTiles[i]);
		if (Reader.Read<bool>() && m_pTiles[i]->tileName != TileName::Border)
		{
			auto m_Random = rand() % 20;
			if (m_Random > 18)
				m_pWalls.push_back(std::make_shared<MovableWallComponent>("tiles.png", (int)i,true));
			else
				m_pWalls.push_back(std::make_shared<MovableWallComponent>("tiles.png", (int)i));
			Locator::RegisterWall(i, m_pWalls[m_pWalls.size() - 1]);
		}
	}

	//Making the special blocks appear on random positions
	for (int i{}; i < 3; i++)
	{
		int random = rand() % m_pWalls.size();
		m_pWalls[random]->SetBonusBlock();
	}
	Reader.CloseFile();

	for (int i{}; i < playerAmount; ++i)
	{
		m_PlayerPositions.push_back(Point2f{});
	}
}

void dae::LevelComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (!m_SetDisabled)
	{
		GetGameObject()->GetComponent<TextComponent>()->DisableNormalRender(true);
		m_SetDisabled = true;
	}

	GetGameObject()->GetComponent<TextComponent>()->SetText(Locator::GetSubject()->GetScoreString());

	for (auto wall : m_pWalls)
	{
		wall->Update(deltaTime);
	}
	if (!m_Activated)
	{
		if (CheckForBonus())
		{
			m_Activated = true;
			Locator::GetSubject()->SetEvent(dae::Subject::Event::Bonus);
			Locator::GetSubject()->SetScoreChanged(true);
			for (auto wall : m_pWalls)
			{
				wall->SetSpecialActive();
			}
			for (auto agent : Locator::GetAgents())
			{
				agent.second->GetComponent<AgentComponent>()->m_IsStunned = true;
			}
		}
	}
}

void dae::LevelComponent::Render()
{
	for (unsigned int i{}; i < m_pTiles.size(); i++)
	{
		if (m_pTiles[i]->tileName == TileName::Black)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{ 0.0f,0.0f,16.0f,16.0f });
		}
		else if (m_pTiles[i]->tileName == TileName::BlockNormal)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{ 16.0f,0.0f,16.0f,16.0f });
		}
		else if (m_pTiles[i]->tileName == TileName::BlockSpecial)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{ 32.0f,0.0f,16.0f,16.0f });
		}
		else if (m_pTiles[i]->tileName == TileName::BlockEnemy)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{ 48.0f,0.0f,16.0f,16.0f });
		}
		else if (m_pTiles[i]->tileName == TileName::Border)
		{
			m_pTiles[i]->Texture->Render(Rectf{ m_pTiles[i]->Position.x,m_pTiles[i]->Position.y,48.0f,48.0f }, Rectf{ 64.0f,0.0f,16.0f,16.0f });
		}
	}
	m_pTiles[0]->Texture->Render(Rectf{ 0.0f,0.0f,48.0f,48.0f }, Rectf{ 64.0f,0.0f,16.0f,16.0f });

	for (auto wall : m_pWalls)
	{
		wall->Render();
	}

	GetGameObject()->GetComponent<TextComponent>()->Render(Point2f{ 380,15 });
}


bool dae::LevelComponent::CheckForBonus()
{
	for (auto wall : m_pWalls)
	{
		if (wall->GetBonusBlock())
		{
			for (auto adjWall : m_pWalls)
			{
				if (wall->GetIndex() + 1 == adjWall->GetIndex() && adjWall->GetBonusBlock())
				{
					for (auto secondAdjWall : m_pWalls)
					{
						if (adjWall->GetIndex() + 1 == secondAdjWall->GetIndex() && secondAdjWall->GetBonusBlock())
							return true;
					}
				}

				if (wall->GetIndex() + 14 == adjWall->GetIndex() && adjWall->GetBonusBlock())
				{
					for (auto secondAdjWall : m_pWalls)
					{
						if (adjWall->GetIndex() + 14 == secondAdjWall->GetIndex() && secondAdjWall->GetBonusBlock())
							return true;
					}
				}

				if (wall->GetIndex() - 1 == adjWall->GetIndex() && adjWall->GetBonusBlock())
				{
					for (auto secondAdjWall : m_pWalls)
					{
						if (adjWall->GetIndex() - 1 == secondAdjWall->GetIndex() && secondAdjWall->GetBonusBlock())
							return true;
					}
				}

				if (wall->GetIndex() - 14 == adjWall->GetIndex() && adjWall->GetBonusBlock())
				{
					for (auto secondAdjWall : m_pWalls)
					{
						if (adjWall->GetIndex() - 14 == secondAdjWall->GetIndex() && secondAdjWall->GetBonusBlock())
							return true;
					}
				}
			}
		}
	}

	return false;
}


