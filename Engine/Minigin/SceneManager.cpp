#include "MiniginPCH.h"
#include "SceneManager.h"
#include "OnePlayerScene.h"
#include "StartMenuScene.h"
#include "Scene.h"


void dae::SceneManager::Update(float deltaTime)
{

	m_ActiveScene->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	m_ActiveScene->Render();
}

std::shared_ptr<dae::Scene> dae::SceneManager::CreateScene(const std::string& name, SceneType type)
{
	std::shared_ptr<Scene> scene;
	switch (type)
	{
	case dae::SceneType::OnePlayerScene:
		scene = std::shared_ptr<OnePlayerScene>(new OnePlayerScene{name});
		break;
	case dae::SceneType::StartMenu:
		scene = std::shared_ptr<StartMenuScene>(new StartMenuScene{name});
		break;
	}
	m_Scenes.push_back(scene);
	return scene;
}

std::shared_ptr<dae::Scene> dae::SceneManager::GetActiveScene()
{
	return m_ActiveScene;
}

void dae::SceneManager::SetActiveScene(std::shared_ptr<Scene> activeScene)
{
	for (auto scene : m_Scenes)
	{
		if (scene == activeScene)
			m_ActiveScene = scene;
	}
}
