#include "MiniginPCH.h"
#include "ServiceLocator.h"


std::map<int, std::shared_ptr<dae::GameObject>> dae::ServiceLocator::m_pPlayers;
std::map<int, std::shared_ptr<dae::GameObject>> dae::ServiceLocator::m_pAgents;
std::map<int,dae::Tile*> dae::ServiceLocator::m_pTiles;
std::shared_ptr<dae::GameObject> dae::ServiceLocator::m_pCollision;