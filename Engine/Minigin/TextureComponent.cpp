#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "Renderer.h"


dae::TextureComponent::TextureComponent(std::string fileName)
	:m_pTexture{ ResourceManager::GetInstance().LoadTexture(fileName) }
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
		const auto pos = GetGameObject()->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}


