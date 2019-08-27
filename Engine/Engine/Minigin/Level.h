#pragma once
#include <vector>
#include "structs.h"
#include "TextureComponent.h"
#include "./../Pengo/MovableWallComponent.h"
namespace dae
{
	
	class LevelComponent: public BaseComponent
	{
	public:
		LevelComponent(std::string levelPath, int playerAmount = 1);
		~LevelComponent()
		{
			for (auto tile : m_pTiles)
			{
				delete tile->Texture;
				delete tile;
				
			}
		}

		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		std::vector<std::shared_ptr<MovableWallComponent>> GetWalls() { return m_pWalls; }

		bool CheckForBonus();

	private:
		std::vector<std::shared_ptr<MovableWallComponent>> m_pWalls;
		std::vector<Tile*> m_pTiles;
		std::vector<Point2f> m_PlayerPositions;
		std::string m_filePath;
		bool m_Activated = false;
		bool m_SetDisabled = false;
	};
}

