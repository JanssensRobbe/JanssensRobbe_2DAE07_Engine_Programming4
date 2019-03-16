#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "Log.h"


dae::BaseComponent::BaseComponent()
	: m_pGameObject(nullptr)
	, m_IsInitialized(false) 
{
	
}

dae::TransformComponent* dae::BaseComponent::GetTransform() const
{
#if _DEBUG
	if (m_pGameObject == nullptr)
	{
		dae::Logger::LogWarning(L"BaseComponent::GetTransform() > Failed to retrieve the TransformComponent. GameObject is NULL.");
		return nullptr;
	}
#endif

	return m_pGameObject->GetTransform();
}


