#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int dae::Scene::idCounter = 0;

dae::Scene::Scene(const std::string& name) : m_Name(name) {}

void dae::Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
}

void dae::Scene::Update(float deltaTime)
{
	for(auto gameObject : m_Objects)
	{
		gameObject->Update(deltaTime);
	}
}

void dae::Scene::Render() const
{
	for (const auto gameObject : m_Objects)
	{
		gameObject->Render();
	}
}

void dae::Scene::SetPlayerPosition(Point2f position, int index)
{
	if (int(m_PlayerPositions.size()) < index)
	{
		m_PlayerPositions[index] = position;
	}
	else
	{
		m_PlayerPositions.push_back(Point2f(position));
	}
}
