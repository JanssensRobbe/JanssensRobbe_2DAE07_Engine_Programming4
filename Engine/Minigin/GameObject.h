#pragma once
#include <memory>
#include <typeinfo>
#include <functional>

#include "Texture2D.h"
#include "SceneObject.h"

namespace dae
{
	class BaseComponent;
	class TransformComponent;
	class GameObject : public SceneObject
	{
	public:

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);

		void Update(float deltaTime) override;
		void Render() const override;

		void SetPosition(float x, float y);

		TransformComponent* GetTransform() const { return m_pTransform; }

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		//credits to Graphics Programming 2 
#pragma region
		template <class T>
		bool HasComponent()
		{
			return GetComponent<T>() != nullptr;
		}

		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}

			return nullptr;
		}

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

		template <class T>
		T* GetChild()
		{
			const type_info& ti = typeid(T);
			for (auto* child : m_pChildren)
			{
				if (child && typeid(*child) == ti)
					return static_cast<T*>(child);
			}
			return nullptr;
		}

		template <class T>
		std::vector<T*> GetChildren()
		{
			const type_info& ti = typeid(T);
			std::vector<T*> children;

			for (auto* child : m_pChildren)
			{
				if (child && typeid(*child) == ti)
					children.push_back((T*)child);
			}
			return children;
		}
#pragma endregion Template Methods
	private:
		dae::TransformComponent* m_pTransform = nullptr;
		std::vector<BaseComponent*> m_pComponents;
		std::vector<BaseComponent*> m_pChildren;
		std::shared_ptr<Texture2D> m_Texture;
	};
}
