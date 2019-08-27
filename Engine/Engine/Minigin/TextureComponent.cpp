#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"


dae::TextureComponent::TextureComponent(std::string fileName)
	:BaseComponent{}
	,m_pTexture{ ResourceManager::GetInstance().LoadTexture(fileName) }
	, m_Pos{ 0.0f,0.0f }
{
}

void dae::TextureComponent::SetTexture(const std::string & filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void dae::TextureComponent::Render()
{
	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_Pos.x, m_Pos.y);
	}
}

void dae::TextureComponent::Render(Rectf destRect, Rectf srcRect) const
{
	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, destRect, srcRect);
	}
}


