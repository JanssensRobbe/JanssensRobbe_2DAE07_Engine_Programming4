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
	float frameWidth{ 128.0f };
	float frameHeight{ 128.0f };
	int row = m_ActFrame / m_Cols;
	int col = m_ActFrame % m_Cols;
	auto pos = GetTransform()->GetPosition();
	Rectf destRect{ pos.x + m_Displacement.x, pos.y + m_Displacement.y, frameWidth, frameHeight};
	Rectf srcRect{ frameWidth * col, frameHeight * row, frameWidth, frameHeight };

	m_pTexture->Render(destRect,srcRect);
}
