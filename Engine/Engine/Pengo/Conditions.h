#pragma once
#include "AgentComponent.h"
#include "./../Minigin/Condition.h"
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
			if (pAgent->m_IsHitByFlyingRock)
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

	class StopBeingStunned final : public Condition
	{
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (!pAgent->m_IsStunned)
			{
				return true;
			}
			return false;
		}
	};

	class IsStunned final : public Condition
	{
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (pAgent->m_IsStunned)
				return true;

			return false;
		}
	};

	class IsChasing final : public Condition
	{
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (pAgent->m_ChasePlayer)
				return true;

			return false;
		}
	};

	class StopChasing final : public Condition
	{
		bool IsTriggered(int idx) override
		{
			auto& pObj = Locator::GetAgent(idx);
			if (pObj == nullptr)
				return false;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return false;
			if (!pAgent->m_ChasePlayer)
				return true;

			return false;
		}
	};
}