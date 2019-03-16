#pragma once
#include "GameObject.h"
namespace dae
{
	class TransformComponent;
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

		GameObject* GetGameObject() const { return m_pGameObject; }
		TransformComponent* GetTransform() const;

	protected:

		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

		GameObject* m_pGameObject;
		bool m_IsInitialized;
	};
}

