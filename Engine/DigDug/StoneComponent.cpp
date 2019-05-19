#include "pch.h"
#include "StoneComponent.h"
#include "TextureComponent.h"

dae::StoneComponent::StoneComponent(TextureComponent* texture, int index, std::vector<dae::Tile*>& tiles)
	:BaseComponent{}
	,m_pTiles{tiles}
	,m_pTexture{texture}
	,m_Index{index}
	,m_IsFalling{false}
	, m_MovementSpeed{50.0f}
{
	m_Position = m_pTiles[m_Index]->Position;
}

dae::StoneComponent::~StoneComponent()
{
	delete m_pTexture;
}

void dae::StoneComponent::Update(float deltaTime)
{
	if (m_pTiles[m_Index]->Position.y <= m_Position.y)
	{
		m_Index += 1;
	}

	if (m_pTiles[m_Index]->tileName == TileName::Black)
	{
		m_IsFalling = true;
	}
	else
	{
		m_IsFalling = false;
	}

	if (m_IsFalling)
	{
		m_Position.y += m_MovementSpeed * deltaTime;
	}
}

void dae::StoneComponent::Render()
{
	m_pTexture->Render(Rectf{m_Position.x,m_Position.y,48.0f,48.0f}, Rectf{ 0,0,48.0f,48.0f });
}