#include "MiniginPCH.h"
#include "SpriteComponent.h"


dae::SpriteComponent::SpriteComponent(const std::string& fileName, const Vector2f& displacement, int nrCols, int nrRows, float frameSec)
	:m_Cols{ nrCols }
	, m_Rows{ nrRows }
	, m_FrameSec{ frameSec }
	, m_Displacement{ displacement }
{
	m_pTexture = new TextureComponent(fileName);
}

dae::SpriteComponent::~SpriteComponent()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

void dae::SpriteComponent::Update(float deltaTime)
{
	m_AccuSec += deltaTime;

	if (m_FrameSec < m_AccuSec)
	{
		++m_ActFrame;
		m_ActFrame %= GetNrFrames();
		m_AccuSec -= m_FrameSec;
	}
}

int dae::SpriteComponent::GetNrFrames() const
{
	return m_Cols * m_Rows;
}

void dae::SpriteComponent::Render()
{
	float frameWidth{ m_pTexture->GetWidth() / m_Cols };
	float frameHeight{ m_pTexture->GetHeight() / m_Rows };

	Rectf destRect{ pos.x + m_Displacement.x, pos.y + m_Displacement.y, frameWidth * scale, frameHeight * scale };
	Rectf srcRect{ frameWidth * m_ActFrame, frameHeight * row, frameWidth, frameHeight };

	m_pTexture->Render(destRect, srcRect);
}

