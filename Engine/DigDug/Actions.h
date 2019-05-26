#pragma once
#include "AgentComponent.h"
#include "Action.h"
#include "TransformComponent.h"
#include "ServiceLocator.h"

namespace dae {
	class WalkAction final : public Action
	{
	public:
		void Invoke(int index) override
		{
			auto& pObj = ServiceLocator::GetAgent(index);
			if (pObj == nullptr)
				return;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return;

			pAgent->Walk();
		}
	};

	class InflateAction final : public Action
	{
	public:
		void Invoke(int index) override
		{
			auto& pObj = ServiceLocator::GetAgent(index);
			if (pObj == nullptr)
				return;
			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return;
			pAgent->Inflate();
		}
	};

	class DeadAction final : public Action
	{
	public:
		void Invoke(int index) override
		{
			auto& pObj = ServiceLocator::GetAgent(index);
			if (pObj == nullptr)
				return;

			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return;

			pAgent->Dead();
		}
	};

	class DisableCollisionAction final : public Action
	{
	public:
		void Invoke(int index) override
		{
			auto pObj = ServiceLocator::GetAgent(index);
			if (pObj == nullptr)
				return;

			auto pAgent = pObj->GetComponent<AgentComponent>();
			if (pAgent == nullptr)
				return;

			pAgent->DisableCollision();

		}
	};
 }