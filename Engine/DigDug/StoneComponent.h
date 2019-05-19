#pragma once
#include "BaseComponent.h"
#include "structs.h"
namespace dae
{
	class TextureComponent;
	class StoneComponent :public BaseComponent
	{
	public:

		StoneComponent(TextureComponent* texture, int index, std::vector<dae::Tile*>& tiles);
		virtual ~StoneComponent();
		StoneComponent(const StoneComponent& other) = delete;
		StoneComponent(StoneComponent&& other) noexcept = delete;
		StoneComponent& operator=(const StoneComponent& other) = delete;
		StoneComponent& operator=(StoneComponent&& other) noexcept = delete;

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

	private:
		std::vector<dae::Tile*>& m_pTiles;
		Point2f m_Position;
		TextureComponent* m_pTexture;
		bool m_IsFalling, m_MayDestroy;
		int m_Index;
		float m_MovementSpeed;
	};
}

