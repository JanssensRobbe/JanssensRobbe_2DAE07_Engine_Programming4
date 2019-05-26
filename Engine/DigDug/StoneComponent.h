#pragma once
#include "BaseComponent.h"
#include "structs.h"
namespace dae
{
	class TextureComponent;
	class StoneComponent :public BaseComponent
	{
	public:

		StoneComponent(TextureComponent& texture, int index);
		~StoneComponent() = default;
		StoneComponent(const StoneComponent& other) = delete;
		StoneComponent(StoneComponent&& other) noexcept = delete;
		StoneComponent& operator=(const StoneComponent& other) = delete;
		StoneComponent& operator=(StoneComponent&& other) noexcept = delete;

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		bool GetIsDead() { return m_IsDead;}

	private:
		Point2f m_Position;
		TextureComponent* m_pTexture;
		bool m_IsFalling, m_MayDestroy, m_IsRegistered, m_IsDead, m_StartTimer;
		int m_Index, m_CollisionIndex;
		float m_MovementSpeed, m_TimerBeforeFall;
	};
}

