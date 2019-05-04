#include "MiniginPCH.h"
#include "TransformComponent.h"

dae::TransformComponent::TransformComponent()
	:BaseComponent{}
	,m_Position{ 0, 0}
{
}


void dae::TransformComponent::SetPosition(const float x, const float y)
{
		m_Position.x = x;
		m_Position.y = y;
}

void dae::TransformComponent::Render() {}

void dae::TransformComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}
