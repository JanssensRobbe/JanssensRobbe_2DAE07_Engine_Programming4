#pragma once
#include "GameObject.h"
namespace dae
{
	class BaseComponent
	{
	public:
		friend class GameObject;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		BaseComponent();
		virtual ~BaseComponent() = default;
		dae::TransformComponent* GetTransform() const;
		GameObject* GetGameObject() const { return m_pGameObject; }

	protected:

		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		GameObject* m_pGameObject;
		bool m_IsInitialized;
	};
}

