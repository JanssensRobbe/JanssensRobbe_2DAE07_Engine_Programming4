#pragma once
#include <iostream>
#include "SpriteComponent.h"
#include "Structs.h"
namespace dae
{
	enum class Direction
	{
		left,
		right,
		up,
		down
	};
	class Command
	{
	public:
		Command(Direction direction) 
			: m_Direction{ direction }
			, m_XLimits{0,672}
			, m_YLimits{70,790}
		{}
		virtual dae::State GetPlayerState() = 0;
		virtual ~Command() {};
		virtual void execute(TransformComponent* transform, float elapsedTime) = 0;
		virtual void render(SpriteComponent* sprite) = 0;
	protected:
		Direction m_Direction;
		Point2f m_XLimits, m_YLimits;
	};

	class WalkCommand : public Command
	{
	private:
		float m_MovementSpeed = 50.0f;
	public:
	
		 void Walk()
		{
			std::cout << "Walk" << std::endl;

		}
		WalkCommand(Direction direction) : Command{direction} {}
		virtual dae::State GetPlayerState() override { return dae::State::Walking; }
		virtual void execute(TransformComponent* transform, float elapsedTime) {
			Walk();
			if (m_Direction == Direction::right )
			{
				if(transform->GetPosition().x + m_MovementSpeed * elapsedTime < m_XLimits.y)
					transform->SetPosition(transform->GetPosition().x + m_MovementSpeed * elapsedTime, 
						transform->GetPosition().y, transform->GetPosition().z);
			}
			else if (m_Direction == Direction::left )
			{
				if(transform->GetPosition().x + m_MovementSpeed * elapsedTime > m_XLimits.x)
					transform->SetPosition(transform->GetPosition().x - m_MovementSpeed * elapsedTime,
						transform->GetPosition().y, transform->GetPosition().z);

			}
			else if (m_Direction == Direction::up )
			{
				if(transform->GetPosition().y - m_MovementSpeed * elapsedTime > m_YLimits.x)
					transform->SetPosition(transform->GetPosition().x , 
						transform->GetPosition().y - m_MovementSpeed * elapsedTime, transform->GetPosition().z);
			}
			else if (m_Direction == Direction::down )
			{
				if(transform->GetPosition().y + m_MovementSpeed * elapsedTime < m_YLimits.y)
					transform->SetPosition(transform->GetPosition().x, 
						transform->GetPosition().y + m_MovementSpeed * elapsedTime, transform->GetPosition().z);
			}
			
		}
		virtual void render(SpriteComponent* sprite)
		{
			sprite->SetColumn(2);
			if (m_Direction == Direction::right)
			{
				sprite->SetRow(9);
			}
			else if (m_Direction == Direction::left)
			{
				sprite->SetRow(12);
			}
			else if (m_Direction == Direction::up)
			{
				sprite->SetRow(0);
			}
			else if (m_Direction == Direction::down)
			{
				sprite->SetRow(18);
			}
		}
	};

	class DigCommand : public Command
	{
	private:
		float m_DigSpeed = 30.0f;
		Direction m_Direction;
	public:
		DigCommand(Direction direction) : Command{ direction } {}
		void Dig() {
			std::cout << "Dig" << std::endl;
		};
		virtual dae::State GetPlayerState() override { return dae::State::Digging; }
		virtual void execute(TransformComponent* transform, float elapsedTime) {
			Dig();
			transform->SetPosition(transform->GetPosition().x + m_DigSpeed * elapsedTime, transform->GetPosition().y, transform->GetPosition().z);
		}
		virtual void render(SpriteComponent* sprite)
		{
			sprite->SetColumn(2);
			sprite->SetRow(8);
		}
	};

	class PumpCommand : public Command
	{
	public:
		PumpCommand(Direction direction):Command{ direction } {}
		void Pump() {
			std::cout << "Pump" << std::endl;
		};
		virtual dae::State GetPlayerState() override { return dae::State::Pumping; }
		virtual void execute(TransformComponent* transform, float elapsedTime) {
			Pump();
			UNREFERENCED_PARAMETER(elapsedTime);
			UNREFERENCED_PARAMETER(transform);
		}
		virtual void render(SpriteComponent* sprite)
		{
			sprite->SetColumn(2);
			sprite->SetRow(7);
		}
	};
}

