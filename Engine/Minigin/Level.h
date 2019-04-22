#pragma once
#include <vector>
#include "structs.h"
#include "TextureComponent.h"
namespace dae
{
	class LevelComponent : public BaseComponent
	{

		struct Tile
		{
			TextureComponent* Texture;
			Point2f Position;
		};

	public:

		LevelComponent();
		virtual ~LevelComponent() = default;

		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		virtual void SetPlayerPosition(Point2f playerPosition);

	private:

		std::vector<Tile*> m_Tiles;
		Point2f m_PlayerPosition;
	};
}

