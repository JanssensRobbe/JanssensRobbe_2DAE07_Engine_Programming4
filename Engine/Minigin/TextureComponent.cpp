#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"


dae::TextureComponent::TextureComponent(std::string fileName)
	:m_pTexture{ ResourceManager::GetInstance().LoadTexture(fileName) }
	, m_DestRect{}
	, m_SrcRect{}
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
		float textLeft{};
		float textRight{};
		float textTop{};
		float textBottom{};
		if (!(m_SrcRect.width > 0.0f && m_SrcRect.height > 0.0f)) // No rect specified, use complete texture
		{
			textLeft = 0.0f;
			textRight = 1.0f;
			textTop = 0.0f;
			textBottom = 1.0f;
		}
		else // Clip specified, convert them to the range [0.0, 1.0]
		{
			textLeft = m_SrcRect.left / m_Width;
			textRight = (m_SrcRect.left + m_SrcRect.width) / m_Width;
			textTop = (m_SrcRect.bottom - m_SrcRect.height) / m_Height;
			textBottom = m_SrcRect.bottom / m_Height;
		}

		const auto pos = GetGameObject()->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}


