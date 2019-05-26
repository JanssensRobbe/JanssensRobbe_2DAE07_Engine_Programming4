#include "MiniginPCH.h"
#include "CollisionComponent.h"

std::vector<std::pair<dae::Tag, Rectf>> dae::CollisionComponent::m_Colliders;
std::vector<bool> dae::CollisionComponent::m_IsActive;

dae::CollisionComponent::CollisionComponent()
{
}

bool dae::CollisionComponent::CheckCollision(Tag collisionTag, Rectf object) const
{
	for (int i{}; i < m_Colliders.size(); ++i)
	{
		if (m_Colliders[i].first.tag == collisionTag.tag && m_IsActive[i])
		{
			if (object.bottom >= m_Colliders[i].second.bottom && object.bottom <= m_Colliders[i].second.bottom + m_Colliders[i].second.height &&
				object.left >= m_Colliders[i].second.left && object.left <= m_Colliders[i].second.left + m_Colliders[i].second.width)
				return true;

			if (object.bottom + object.height >= m_Colliders[i].second.bottom && object.bottom + object.height <= m_Colliders[i].second.bottom + m_Colliders[i].second.height &&
				object.left >= m_Colliders[i].second.left && object.left <= m_Colliders[i].second.left + m_Colliders[i].second.width)
				return true;

			if (object.bottom + object.height >= m_Colliders[i].second.bottom && object.bottom + object.height <= m_Colliders[i].second.bottom + m_Colliders[i].second.height &&
				object.left + object.width >= m_Colliders[i].second.left && object.left + object.width <= m_Colliders[i].second.left + m_Colliders[i].second.width)
				return true;

			if (object.bottom >= m_Colliders[i].second.bottom && object.bottom <= m_Colliders[i].second.bottom + m_Colliders[i].second.height &&
				object.left + object.width >= m_Colliders[i].second.left && object.left + object.width <= m_Colliders[i].second.left + m_Colliders[i].second.width)
				return true;
		}
	}
	return false;
}


