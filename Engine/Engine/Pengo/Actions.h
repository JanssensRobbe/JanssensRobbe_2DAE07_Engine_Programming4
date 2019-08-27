#pragma once
#include "AgentComponent.h"
#include "./../Minigin/Action.h"
#include "TransformComponent.h"
#include "Locator.h"

namespace dae {
	class WalkAction final : public Action
	{
	public:
		void Invoke(int index) override
		{
			auto& pObj = Locator::GetAgent(index);
			if (pObj == nullptr)
				return;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return;

			pAgent->Walk();
		}
	};

	class StunAction final : public Action
	{
	public:
		void Invoke(int index) override
		{
			auto& pObj = Locator::GetAgent(index);
			if (pObj == nullptr)
				return;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return;

			pAgent->Stun();
		}
	};

	class ChaseAction final : public Action
	{
	public:
		void Invoke(int index) override
		{
			auto& pObj = Locator::GetAgent(index);
			if (pObj == nullptr)
				return;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return;

			pAgent->GetClosestPlayer();
		}
	};

	class DeadAction final : public Action
	{
	public:
		void Invoke(int index) override
		{
			auto& pObj = Locator::GetAgent(index);
			if (pObj == nullptr)
				return;

			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return;

			pAgent->Dead();
		}
	};

	class FollowRockAction final : public Action
	{
	public:
		void Invoke(int index) override
		{
			auto pObj = Locator::GetAgent(index);
			if (pObj == nullptr)
				return;

			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return;

			pAgent->FollowRock();

		}
	};


	class DisableCollisionAction final : public Action
	{
	public:
		void Invoke(int index) override
		{
			auto pObj = Locator::GetAgent(index);
			if (pObj == nullptr)
				return;

			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return;

			pAgent->DisableCollision();

		}
	};
 }