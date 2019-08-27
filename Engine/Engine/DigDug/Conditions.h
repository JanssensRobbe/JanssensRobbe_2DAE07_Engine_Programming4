#pragma once
#include "AgentComponent.h"
#include "Condition.h"
#include "Locator.h"

namespace dae {
	class StartGoingInvisible final : public Condition
	{
	public:
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (pAgent->m_IsInvis && !pAgent->m_WasInvis)
			{
				pAgent->m_WasInvis = true;
				return true;
			}
			return false;
		}
	};

	class StopGoingInvisible final : public Condition
	{
	public:
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (!pAgent->m_IsInvis && pAgent->m_WasInvis)
			{
				pAgent->m_WasInvis = false;
				return true;
			}
			return false;
		}
	};

	class StartBeingInflated final : public Condition
	{
	public:
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (pAgent->m_IsBeingInflated && pAgent->m_WasBeingInflated == false)
			{
				pAgent->m_WasBeingInflated = true;
				return true;
			}
			return false;
		}

	};

	class StopBeingInflated final : public Condition
	{
	public:
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (!pAgent->m_IsBeingInflated && pAgent->m_WasBeingInflated && !pAgent->m_IsDead)
			{
				pAgent->m_WasBeingInflated = false;
				return true;
			}
			return false;
		}
	};

	class IsDead final : public Condition
	{
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (pAgent->m_IsDead)
			{
				return true;
			}
			return false;
		}
	};

	class IsHitByRock final : public Condition
	{
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (pAgent->m_IsHitByFallingRock)
			{
				return true;
			}
			return false;
		}
	};

	class StopBeingIdle final : public Condition
	{
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (!pAgent->m_IsIdle)
			{
				return true;
			}
			return false;
		}
	};
}