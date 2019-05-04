#include "MiniginPCH.h"
#include "ButtonComponent.h"
#include "InputManager.h"




dae::ButtonComponent::ButtonComponent(Rectf destRect, TextureComponent& texture)
	:m_DestRect{destRect}
	, m_pTexture{&texture}
	,m_ActiveButton{true}
	,m_SceneName{""}
	,m_SceneType{SceneType::None}
{
	m_pTexture->SetPosition(Point2f{ destRect.left,destRect.bottom });
}

void dae::ButtonComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	auto command = InputManager::GetInstance().handleInput();
	if (m_ActiveButton && command->GetIsButton() && m_SceneType != SceneType::None)
	{
		SceneManager::GetInstance().CreateScene(m_SceneName,m_SceneType);
	}
}

void dae::ButtonComponent::Render()
{
}

void dae::ButtonComponent::SetLoadedScene(std::string name, SceneType scene)
{
	m_SceneName = name;
	m_SceneType = scene;
}
