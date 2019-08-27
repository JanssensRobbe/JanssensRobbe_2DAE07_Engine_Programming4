#include "MiniginPCH.h"
#include "Locator.h"

std::map<int, std::shared_ptr<dae::GameObject>> dae::Locator::m_pPlayers;
std::map<int, std::shared_ptr<dae::GameObject>> dae::Locator::m_pAgents;
std::map<int,dae::Tile*> dae::Locator::m_pTiles;
std::map<int, std::shared_ptr<dae::MovableWallComponent>> dae::Locator::m_pWalls;
std::shared_ptr<dae::GameObject> dae::Locator::m_pCollision;
dae::Subject* dae::Locator::m_pSubject;