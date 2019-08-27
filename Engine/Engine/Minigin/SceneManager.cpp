#include "MiniginPCH.h"
#include "SceneManager.h"
#include "CharacterComponent.h"
#include "./../DigDug/StartMenuScene.h"
#include "./../DigDug/OnePlayerScene.h"
#include "./../DigDug/TwoPlayerScene.h"
#include "Scene.h"
#include "Locator.h"


void dae::SceneManager::Update(float deltaTime)
{

	m_ActiveScene->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	m_ActiveScene->Render();
}

std::shared_ptr<dae::Scene> dae::SceneManager::CreateScene(SceneType type, std::shared_ptr<Scene> scene)
{
	m_Scenes.push_back(std::make_pair(type, scene));
	return scene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetActiveScene()
{
	return m_ActiveScene;
}

void dae::SceneManager::SetActiveScene(std::shared_ptr<Scene> activeScene)
{
	m_ActiveScene = activeScene;
}

void dae::SceneManager::DeleteScene(std::string name)
{
	for (unsigned int i{};i< m_Scenes.size(); i++)
	{
		if (m_Scenes[i].second->GetName() == name)
		{
			m_Scenes[i] = m_Scenes[m_Scenes.size() - 1];
			m_Scenes.pop_back();
		}

	}
}
