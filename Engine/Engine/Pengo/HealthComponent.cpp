#include "pch.h"
#include "HealthComponent.h"
#include "TextureComponent.h"
#include "Locator.h"

dae::HealthComponent::HealthComponent(const std::string& name, int index,Point2f position, int health)
	:m_Health(health)
	, m_pTexture(new TextureComponent{name})
	, m_Index(index)
	, m_Size(32.0f)
	, m_Pos{ position }
{
	
}


dae::HealthComponent::~HealthComponent()
{
	delete m_pTexture;
}

void dae::HealthComponent::Render()
{
	for (int i{}; i < m_Health; i++)
	{
		m_pTexture->Render(Rectf{m_Pos.x + i * m_Size,m_Pos.y,m_Size,m_Size }, Rectf{ 0.0f,0.0f,224.0f,224.0f});
	}
}

void dae::HealthComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

int dae::HealthComponent::DecreaseHealth()
{
	--m_Health;
	return m_Health;
}
