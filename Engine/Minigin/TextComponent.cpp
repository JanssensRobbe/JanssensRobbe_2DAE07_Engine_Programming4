#include "MiniginPCH.h"

#include "TextComponent.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include <iostream>
#include <string>


dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font, SDL_Color color, bool IsFpsCountOn)
	:BaseComponent{}
	,m_NeedsUpdate(true )
	, m_Text(text)
	, m_Font(font)
	, m_Texture(nullptr)
	, m_FpsCount(0)
	, m_IsFpsOn( IsFpsCountOn )
	, m_Color(color)
{ }

void dae::TextComponent::Update(float deltaTime)
{
	if (m_IsFpsOn)
	{
		m_FpsCount = int(1 / deltaTime);
		m_Text = std::to_string(m_FpsCount);
	}
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
	}
}

void dae::TextComponent::Render()
{
	if (m_Texture != nullptr)
	{
		const auto pos = GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}


