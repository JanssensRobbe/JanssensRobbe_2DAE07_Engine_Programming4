#include "MiniginPCH.h"
#include "SceneManager.h"
#include "OnePlayerScene.h"
#include "StartMenuScene.h"


void dae::SceneManager::Update(float deltaTime)
{
	for(auto scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : m_Scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name, SceneType type)
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
	return *scene;
}

dae::Scene& dae::SceneManager::GetActiveScene()
{
	return *m_Scenes[0];
}
