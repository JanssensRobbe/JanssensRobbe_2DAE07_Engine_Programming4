#include "MiniginPCH.h"
#include "SpriteComponent.h"



dae::SpriteComponent::SpriteComponent(const std::string& fileName, int nrCols, int nrRows, float frameSec, float frameSize, int startRow, float size)
	:BaseComponent{}
	,m_Cols{ nrCols }
	, m_Rows{ nrRows }
	, m_FrameSec{ frameSec }
	, m_FrameSize{frameSize}
	, m_StartRow{startRow}
	, m_Size{size}
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
	int row = m_StartRow + m_ActFrame / m_Cols;
	if (row > m_Rows)
		row -= m_Rows;
	int col = m_ActFrame % m_Cols;
	auto pos = GetTransform()->GetPosition();
	Rectf destRect{ pos.x, pos.y, m_FrameSize * m_Size, m_FrameSize * m_Size };
	Rectf srcRect{ m_FrameSize * col, m_FrameSize * row, m_FrameSize, m_FrameSize };

	m_pTexture->Render(destRect, srcRect);
}