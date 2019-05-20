#include "MiniginPCH.h"
#include "SceneManager.h"
#include "CharacterComponent.h"
#include "./../DigDug/StartMenuScene.h"
#include "./../DigDug/OnePlayerScene.h"
#include "./../DigDug/TwoPlayerScene.h"
#include "Scene.h"


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

void dae::SceneManager::SetActiveScene(SceneType activeScene)
{
	for (auto scene : m_Scenes)
	{
		if (scene.first == activeScene)
			m_ActiveScene = scene.second;
	}
}
