#include "pch.h"
#include "ButtonComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "OnePlayerScene.h"
#include "TwoPlayerScene.h"
#include "VersusScene.h"
#include "StartMenuScene.h"
#include "Locator.h"

dae::ButtonComponent::ButtonComponent(Rectf destRect, std::string texture)
	:m_DestRect{destRect}
	, m_pTexture{ new TextureComponent{texture} }
	,m_ActiveButton{false}
	, m_LoadScene{ false }
	,m_SceneType{SceneType::None}
{
	m_pTexture->SetPosition(Point2f{ destRect.left,destRect.bottom });
}

void dae::ButtonComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_LoadScene)
	{
		Locator::UnregisterAll();
		SceneManager::GetInstance().CreateScene(m_SceneType, m_Scene);
		SceneManager::GetInstance().DeleteScene("GameOverScene");
		SceneManager::GetInstance().SetActiveScene(m_Scene);
	}
}

void dae::ButtonComponent::Render()
{
	
	if(!m_ActiveButton)
		m_pTexture->Render(m_DestRect, Rectf{0,0,m_DestRect.width,m_DestRect.height});
	else
		m_pTexture->Render(m_DestRect, Rectf{ 0,m_DestRect.height,m_DestRect.width,m_DestRect.height });
}

void dae::ButtonComponent::SetLoadedScene(std::string name, SceneType scene)
{
	m_SceneType = scene;
	switch (scene)
	{
	case dae::SceneType::OnePlayerScene:
		m_Scene = std::make_shared<OnePlayerScene>(name);
		break;
	case dae::SceneType::TwoPlayerScene:
		m_Scene = std::make_shared<TwoPlayerScene>(name);
		break;
	case dae::SceneType::VersusScene:
		m_Scene = std::make_shared<VersusScene>(name);
		break;
	case dae::SceneType::StartMenu:
		m_Scene = std::make_shared<StartMenuScene>(name);
		break;
	case dae::SceneType::None:
		break;
	default:
		break;
	}
}
