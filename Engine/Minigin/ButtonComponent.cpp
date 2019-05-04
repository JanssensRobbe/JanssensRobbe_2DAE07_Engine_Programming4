#include "MiniginPCH.h"
#include "ButtonComponent.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"



dae::ButtonComponent::ButtonComponent(Rectf destRect, std::string texture)
	:m_DestRect{destRect}
	, m_pTexture{ new TextureComponent{texture} }
	,m_ActiveButton{false}
	,m_SceneName{""}
	,m_SceneType{SceneType::None}
{
	m_pTexture->SetPosition(Point2f{ destRect.left,destRect.bottom });
}

void dae::ButtonComponent::Update(float deltaTime)
{

	UNREFERENCED_PARAMETER(deltaTime);
}

void dae::ButtonComponent::Render()
{
	if (m_LoadScene)
	{
		std::shared_ptr<Scene> scene = SceneManager::GetInstance().CreateScene(m_SceneName, m_SceneType);
		scene->LoadScene();
		SceneManager::GetInstance().SetActiveScene(scene);
	}
	if(!m_ActiveButton)
		m_pTexture->Render(m_DestRect, Rectf{0,0,m_DestRect.width,m_DestRect.height});
	else
		m_pTexture->Render(m_DestRect, Rectf{ 0,m_DestRect.height,m_DestRect.width,m_DestRect.height });
}

void dae::ButtonComponent::SetLoadedScene(std::string name, SceneType scene)
{
	m_SceneName = name;
	m_SceneType = scene;
}
