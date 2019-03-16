#pragma once
#include <memory>
#include <typeinfo>
#include <functional>

#include "Texture2D.h"
#include "SceneObject.h"

namespace dae
{
	class TransformComponent;
	class BaseComponent;
	class GameObject : public SceneObject
	{
	public:

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);

		void RootUpdate(float deltaTime);
		virtual void Update(float deltaTime) { UNREFERENCED_PARAMETER(deltaTime); }
		void Render() const override;

		void SetPosition(float x, float y);

		TransformComponent* GetTransform() const { return m_pTransform; }

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
#pragma region

		template <class T>
		std::vector<T*> GetComponents()
		{
			const type_info& ti = typeid(T);
			std::vector<T*> components;

			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					components.push_back(static_cast<T*>(component));
			}

			return components;
		}
#pragma endregion Template Methods
	private:
		dae::TransformComponent* m_pTransform = nullptr;
		std::vector<BaseComponent*> m_pComponents;
		std::shared_ptr<Texture2D> m_Texture;
	};
}
