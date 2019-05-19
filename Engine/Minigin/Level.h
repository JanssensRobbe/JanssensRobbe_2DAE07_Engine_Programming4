#pragma once
#include <vector>
#include "structs.h"
#include "TextureComponent.h"
#include "./../DigDug/StoneComponent.h"
namespace dae
{
	
	class LevelComponent: public BaseComponent
	{
	public:
		LevelComponent();
		virtual ~LevelComponent()
		{
			for (auto tile : m_pTiles)
			{
				delete tile->Texture;
				delete tile;
			}
			for (auto stone : m_pStones)
			{
				delete stone;
			}
		}

		virtual void Update(float deltaTime) override;
		virtual void Render() override;
	private:

		std::vector<StoneComponent*> m_pStones;
		std::vector<Tile*> m_pTiles;
		std::vector<Point2f> m_PlayerPositions;
	};
}

