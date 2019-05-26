#pragma once
#include "ButtonManager.h"
#include "CharacterComponent.h"
#include "CollisionComponent.h"
#include <map>

//////////////////////////////////////////////////////////////////
// Most of this is based on Groupsprojects.                     //
// We created a targetManager that acts like a service allocator//
//////////////////////////////////////////////////////////////////

namespace dae {
	class ServiceLocator
	{
	public:
		static void RegisterPlayer(int index,std::shared_ptr<GameObject>& service){m_pPlayers.insert({ index, service });}
		static void RegisterAgent( int index,std::shared_ptr<GameObject>& service){m_pAgents.insert({ index,service });}
		static void RegisterTile(int index, dae::Tile* tile){m_pTiles.insert({ index,tile});}
		static void RegisterCollisionComponent(std::shared_ptr<GameObject>& collision) { m_pCollision = collision; }

		static std::shared_ptr<GameObject>& GetPlayer(int index) { return m_pPlayers.find(index)->second; }
		static std::map<int, std::shared_ptr<GameObject>>& GetPlayers() { return m_pPlayers; }

		static std::shared_ptr<GameObject>& GetAgent(int index) { return m_pAgents.find(index)->second; }
		static std::map<int, std::shared_ptr<GameObject>>& GetAgents() { return m_pAgents; }

		static dae::Tile* GetTile(int index) { return m_pTiles.find(index)->second; }
		static std::map<int, dae::Tile*>& GetTiles() { return m_pTiles; }

		static std::shared_ptr<GameObject>& GetCollisionComponent() { return m_pCollision; }
	private:
		static std::map<int, std::shared_ptr<GameObject>> m_pPlayers;
		static std::map<int, std::shared_ptr<GameObject>> m_pAgents;
		static std::map<int, dae::Tile*> m_pTiles;
		static std::shared_ptr<GameObject> m_pCollision;
	};
}

