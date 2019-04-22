#include "MiniginPCH.h"
#include "Level.h"


dae::LevelComponent::LevelComponent()
	:m_PlayerPosition{0.0f,0.0f}
{
	for (int i{}; i < 672; i += 16)
	{
		for (int j{}; j < 864; j += 16)
		{		
				m_Tiles.push_back( new Tile{ new TextureComponent{ "Ground.png" }, Point2f{ float(i),float(j) }});
		}
	}
}

void dae::LevelComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	
}

void dae::LevelComponent::Render()
{
	for (int i{}; i < m_Tiles.size(); i++)
	{
		if (m_Tiles[i]->Position.y <= 96)
		{
			m_Tiles[i]->Texture->Render(Rectf{ m_Tiles[i]->Position.x,m_Tiles[i]->Position.y,48.0f,48.0f }, Rectf{64.0f,0.0f,16.0f,16.0f});
		}
		else if (m_Tiles[i]->Position.y <= 288)
		{
			m_Tiles[i]->Texture->Render(Rectf{ m_Tiles[i]->Position.x,m_Tiles[i]->Position.y,48.0f,48.0f }, Rectf{ 48.0f,0.0f,16.0f,16.0f });
		}
		else if (m_Tiles[i]->Position.y <= 480)
		{
			m_Tiles[i]->Texture->Render(Rectf{ m_Tiles[i]->Position.x,m_Tiles[i]->Position.y,48.0f,48.0f }, Rectf{ 32.0f,0.0f,16.0f,16.0f });
		}
		else if (m_Tiles[i]->Position.y <= 672)
		{
			m_Tiles[i]->Texture->Render(Rectf{ m_Tiles[i]->Position.x,m_Tiles[i]->Position.y,48.0f,48.0f }, Rectf{ 16.0f,0.0f,16.0f,16.0f });
		}
		else if (m_Tiles[i]->Position.y <= 816)
		{
			m_Tiles[i]->Texture->Render(Rectf{ m_Tiles[i]->Position.x,m_Tiles[i]->Position.y,48.0f,48.0f }, Rectf{ 0.0f,0.0f,16.0f,16.0f });
		}
		else
		{
			m_Tiles[i]->Texture->Render(Rectf{ m_Tiles[i]->Position.x,m_Tiles[i]->Position.y,48.0f,48.0f }, Rectf{ 80.0f,0.0f,16.0f,16.0f });
		}

	}
}

void dae::LevelComponent::SetPlayerPosition(Point2f playerPosition)
{
	m_PlayerPosition = playerPosition;
}


