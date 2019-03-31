#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

dae::GameObject::GameObject()
	:m_pComponents(std::vector<BaseComponent*>())
	,m_pTransform{new TransformComponent{}}
{
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{

	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Render();
	}
}


void dae::GameObject::SetPosition(float x, float y, float z)
{
	m_pTransform->SetPosition(x, y, z);
}

void dae::GameObject::AddComponent(dae::BaseComponent* pComp)
{
#if _DEBUG

	for (auto *component : m_pComponents)
	{
		if (component == pComp)
		{
			dae::Logger::LogWarning(L"GameObject::AddComponent > GameObject already contains this component!");
			return;
		}
	}
#endif

	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = this;
}

void dae::GameObject::RemoveComponent(dae::BaseComponent* pComp)
{
	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);

#if _DEBUG
	if (it == m_pComponents.end())
	{
		dae::Logger::LogWarning(L"GameObject::RemoveComponent > Component is not attached to this GameObject!");
		return;
	}

	if (typeid(*pComp) == typeid(dae::TransformComponent))
	{
		dae::Logger::LogWarning(L"GameObject::RemoveComponent > TransformComponent can't be removed!");
		return;
	}
#endif

	m_pComponents.erase(it);
	pComp->m_pGameObject = nullptr;
}
