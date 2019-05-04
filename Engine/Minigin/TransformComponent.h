#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "Structs.h"



namespace dae
{
	class TransformComponent final: public BaseComponent
	{
	private:
		Point2f m_Position;
	public:
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		TransformComponent();
		virtual ~TransformComponent() = default;

		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		const Point2f& GetPosition() const { return m_Position; }
		void SetPosition(const float x, const float y);
	};
}
