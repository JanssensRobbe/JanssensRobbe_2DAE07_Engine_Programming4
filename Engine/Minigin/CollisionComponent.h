#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include <vector>
namespace dae {
	class CollisionComponent :public BaseComponent
	{
	public:
		CollisionComponent();
		virtual ~CollisionComponent() = default;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;

		virtual void Update(float) override {};
		virtual void Render() override {};

		int AddCollider(Tag tag, Rectf collisionBox) { 
			m_Colliders.push_back({ tag, collisionBox });
			m_IsActive.push_back(true);
			++m_LastPosition;
			return m_LastPosition;
		}
		void UpdateCollision(int index, Rectf collsionBox)
		{
			m_Colliders[index].second = collsionBox;
		}
		bool CheckCollision(Tag collisionTag, Rectf object) const;
		void SetActive(int index, bool state) { m_IsActive[index] = state; }
		static std::vector<std::pair<Tag, Rectf>>& GetCollisionObjects() { return m_Colliders; }
	private:
		static std::vector<std::pair<Tag, Rectf>> m_Colliders;
		static std::vector<bool> m_IsActive;
		int m_LastPosition = -1;
	};
}

