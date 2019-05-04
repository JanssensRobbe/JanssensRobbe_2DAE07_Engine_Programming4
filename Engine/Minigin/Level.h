#pragma once
#include <vector>
#include "structs.h"
#include "TextureComponent.h"
namespace dae
{
	class LevelComponent : public BaseComponent
	{
		enum class TileName
		{
			Sky,
			Ground1,
			Ground2,
			Ground3,
			Ground4,
			Black
		};

		struct Tile  
		{
			TextureComponent* Texture;
			Point2f Position;
			TileName tileName;
		};

	public:

		LevelComponent();
		virtual ~LevelComponent()
		{
			for (auto tile : m_pTiles)
			{
				delete tile->Texture;
				delete tile;
			}
		}

		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		virtual void SetPlayerPosition(Point2f playerPosition);
	private:

		std::vector<Tile*> m_pTiles;
		Point2f m_PlayerPosition;
	};
}

