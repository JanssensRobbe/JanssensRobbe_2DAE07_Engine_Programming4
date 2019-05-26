#include "pch.h"
#include "StoneComponent.h"
#include "TextureComponent.h"
#include "../Minigin/SceneManager.h"
#include "ServiceLocator.h"

dae::StoneComponent::StoneComponent(TextureComponent& texture, int index)
	:BaseComponent{}
	,m_pTexture{&texture}
	,m_Index{index}
	,m_IsFalling{false}
	, m_MovementSpeed{50.0f}
	, m_IsRegistered{false}
	, m_CollisionIndex{}
	, m_IsDead{false}
	, m_TimerBeforeFall{1.0f}
	, m_StartTimer{ false }
{
	
	m_Position = ServiceLocator::GetTile(m_Index)->Position;
}

void dae::StoneComponent::Update(float deltaTime)
{
	if (m_StartTimer && m_TimerBeforeFall > 0.0f)
		m_TimerBeforeFall -= deltaTime;
	else if (m_TimerBeforeFall <= 0.0f)
		m_IsFalling = true;

	auto boundries = SceneManager::GetInstance().GetBoundries();
	if (!m_IsRegistered)
	{
		m_CollisionIndex = ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->AddCollider(Tag{ "Stone" }, Rectf{ m_Position.x,m_Position.y,48.0f,48.0f });
		m_IsRegistered = true;
	}
	if (m_IsFalling)
	{
		ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex,true);
		ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->UpdateCollision(m_CollisionIndex, Rectf{ m_Position.x,m_Position.y,48.0f,48.0f });
	}
	else
		ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex,false);

	if (boundries.bottom + boundries.height > m_Position.y)
	{
		if (ServiceLocator::GetTile(m_Index)->Position.y <= m_Position.y)
		{
			m_Index += 14;
		}

		if (ServiceLocator::GetTile(m_Index)->tileName == TileName::Black)
		{
			m_StartTimer = true;
		}
		else if( m_IsFalling)
		{
			m_IsFalling = false;
			m_IsDead = true;
			ServiceLocator::GetCollisionComponent()->GetComponent<CollisionComponent>()->SetActive(m_CollisionIndex,false);
		}

		if (m_IsFalling)
		{
			m_Position.y += m_MovementSpeed * deltaTime;
		}
	}
	else
	{
		m_Position.y = boundries.bottom + boundries.height;
		m_IsFalling = false;
	}
}

void dae::StoneComponent::Render()
{
	m_pTexture->Render(Rectf{m_Position.x,m_Position.y,48.0f,48.0f}, Rectf{ 0,0,48.0f,48.0f });
}