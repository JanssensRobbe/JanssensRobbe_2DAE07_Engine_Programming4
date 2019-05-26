#pragma once
#include "BaseComponent.h"
namespace dae
{
	class TextureComponent;
	class HealthComponent :public BaseComponent
	{
	public:
		HealthComponent(const std::string& name, int index, Point2f position, int health = 3);
		~HealthComponent();
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) noexcept = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

		virtual void Render() override;
		virtual void Update(float deltaTime) override;

		int DecreaseHealth();
	private:
		int m_Health = 0;
		int m_Index = 0;
		float m_Size = 0.0f;
		Point2f m_Pos;
		TextureComponent* m_pTexture = nullptr;
	};
}

