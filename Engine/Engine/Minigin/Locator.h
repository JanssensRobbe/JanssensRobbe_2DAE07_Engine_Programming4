#pragma once
#include "ButtonManager.h"
#include "CharacterComponent.h"
#include "CollisionComponent.h"
#include "./../Pengo/MovableWallComponent.h"
#include <map>
#include "Subject.h"

//////////////////////////////////////////////////////////////////
// Most of this is based on Groupsprojects.                     //
// We created a targetManager that acts like a allocator		//
//////////////////////////////////////////////////////////////////

namespace dae {
	class Locator
	{
	public:
		static void RegisterPlayer(int index,std::shared_ptr<GameObject>& service){
			m_pPlayers.insert({ index, service });
		}
		static void RegisterAgent(int index,std::shared_ptr<GameObject>& service){
			m_pAgents.insert({ index,service });
		}

		static void RegisterTile(int index, dae::Tile* tile){m_pTiles.insert({ index,tile});}
		static void RegisterWall(int index, std::shared_ptr<dae::MovableWallComponent>& wall) { m_pWalls.insert({ index,wall }); }
		static void RegisterCollisionComponent(std::shared_ptr<GameObject>& collision) { m_pCollision = collision; }

		static std::shared_ptr<GameObject>& GetPlayer(int index) { return m_pPlayers.find(index)->second; }
		static std::map<int, std::shared_ptr<GameObject>>&  GetPlayers() {return m_pPlayers;}

		static std::shared_ptr<GameObject>& GetAgent(int index) { return m_pAgents.find(index)->second; }
		static std::map<int, std::shared_ptr<GameObject>>& GetAgents() { return m_pAgents; }

		static dae::Tile* GetTile(int index) { return m_pTiles.find(index)->second; }
		static std::map<int, dae::Tile*>& GetTiles() { return m_pTiles; }

		static std::shared_ptr<dae::MovableWallComponent>& GetWall(int index) { return m_pWalls.find(index)->second; }
		static std::map<int, std::shared_ptr<dae::MovableWallComponent>>& Getwalls() { return m_pWalls; }

		static std::shared_ptr<GameObject>& GetCollisionComponent() { return m_pCollision; }

		static void SetSubject(Subject* subject) { m_pSubject = subject; }
		static Subject* GetSubject() { return m_pSubject; }
		static void UnregisterAll()
		{
			m_pAgents.clear();
			m_pPlayers.clear();
			m_pTiles.clear();
			m_pWalls.clear();
			m_pSubject = nullptr;
			delete m_pSubject;
		}

	private:
		static std::map<int, std::shared_ptr<GameObject>> m_pPlayers;
		static std::map<int, std::shared_ptr<GameObject>> m_pAgents;
		static std::map<int, dae::Tile*> m_pTiles;
		static std::map<int, std::shared_ptr<dae::MovableWallComponent>> m_pWalls;
		static std::shared_ptr<GameObject> m_pCollision;
		static Subject* m_pSubject;
	};
}

