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
			, m_XLimits{0,624}
			, m_YLimits{48,768}
		{}
		virtual dae::State GetPlayerState() = 0;
		virtual bool GetIsButton() = 0;
		virtual dae::Direction getPlayerDirection() { return m_Direction; }
		virtual void SetPreviousDirection(Direction direction) { m_PreviousDirection = direction; }
		virtual bool GetUsePrevious() { return m_UsePreviousDirection; }
		virtual ~Command() {};
		virtual void execute(TransformComponent* transform, float elapsedTime) = 0;
		virtual void render(SpriteComponent* sprite, bool usePrevious) = 0;
	protected:
		Direction m_Direction;
		Direction m_PreviousDirection;
		bool m_UsePreviousDirection = false;
		Point2f m_XLimits, m_YLimits;
		void Move(float speed, float elapsedTime, TransformComponent* transform)
		{
			auto pos = transform->GetPosition();
			auto newPos = speed * elapsedTime;
			if (m_Direction == Direction::right)
			{
				if (pos.x + newPos < m_XLimits.y
					&& int(pos.y) % 48 == 0){
					m_UsePreviousDirection = false;
					transform->SetPosition(pos.x + newPos,pos.y);
				}
				else if (pos.x + newPos >= m_XLimits.y)
					transform->SetPosition(m_XLimits.y, pos.y);
				else if (int(pos.y) % 48 != 0)
				{
					m_UsePreviousDirection = true;
					if (int(pos.y) % 48 < 1)
					{
						transform->SetPosition(pos.x, int(pos.y / 48.0f)*48.0f);
					}
					else
					{
						if (m_PreviousDirection == Direction::up)
							transform->SetPosition(pos.x, pos.y - newPos);
						else if (m_PreviousDirection == Direction::down)
							transform->SetPosition(pos.x, pos.y + newPos);
					}
				}
			}
			else if (m_Direction == Direction::left)
			{
				if (pos.x + newPos > m_XLimits.x
					&& int(pos.y) % 48 == 0) {
					transform->SetPosition(pos.x - newPos,pos.y);
					m_UsePreviousDirection = false;
				}
				else if (pos.x + newPos < m_XLimits.x)
					transform->SetPosition(m_XLimits.x, pos.y);
				else if (int(pos.y) % 48 != 0)
				{
					m_UsePreviousDirection = true;
					if (int(pos.y) % 48 < 1)
					{
						transform->SetPosition(pos.x, int(pos.y / 48.0f)*48.0f);
					}
					else
					{
						if (m_PreviousDirection == Direction::up)
							transform->SetPosition(pos.x, pos.y - newPos);
						else if (m_PreviousDirection == Direction::down)
							transform->SetPosition(pos.x, pos.y + newPos);
					}
				}

			}
			else if (m_Direction == Direction::up)
			{
				if (pos.y - newPos > m_YLimits.x
					&& int(pos.x) % 48 == 0) {
					transform->SetPosition(pos.x, pos.y - newPos);
					m_UsePreviousDirection = false;
				}
				else if (pos.y + speed * elapsedTime < m_YLimits.x)
					transform->SetPosition(pos.x, m_YLimits.x);
				else if (int(pos.x) % 48 != 0)
				{
					m_UsePreviousDirection = true;
					if (int(pos.x) % 48 < 1)
					{
						transform->SetPosition(int(pos.x / 48.0f)*48.0f, pos.y);
					}
					else
					{
						if (m_PreviousDirection == Direction::left)
						{
							transform->SetPosition(pos.x - newPos, pos.y);
						}
						else if (m_PreviousDirection == Direction::right)
						{
							transform->SetPosition(pos.x + newPos, pos.y);
						}
					}
				}
			}
			else if (m_Direction == Direction::down)
			{
				if (pos.y + newPos < m_YLimits.y
					&& int(pos.x) % 48 == 0) {
					m_UsePreviousDirection = false;
					transform->SetPosition(pos.x, pos.y + newPos);
				}
				else if (pos.y + newPos >= m_YLimits.y)
					transform->SetPosition(pos.x, m_YLimits.y);
				else if (int(pos.x) % 48 != 0)
				{
					m_UsePreviousDirection = true;
					if (int(pos.x) % 48 < 1)
					{
						transform->SetPosition(int(pos.x / 48.0f)*48.0f, pos.y);
					}
					else
					{
						if (m_PreviousDirection == Direction::left)
						{
							transform->SetPosition(pos.x - newPos, pos.y);
						}
						else if(m_PreviousDirection == Direction::right)
						{
							transform->SetPosition(pos.x + newPos, pos.y);
						}
					}
				}	
			}
		}
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
		virtual bool GetIsButton() override { return false; }
		virtual dae::State GetPlayerState() override { return dae::State::Walking; }
		virtual void execute(TransformComponent* transform, float elapsedTime) {
			Walk();
			Move(m_MovementSpeed, elapsedTime, transform);
		}
		virtual void render(SpriteComponent* sprite, bool usePrevious)
		{
			sprite->SetColumn(2);
			if (m_Direction == Direction::right && usePrevious == false
				|| m_PreviousDirection == Direction::right && usePrevious == true)
			{
				sprite->SetRow(9);
			}
			else if (m_Direction == Direction::left && usePrevious == false
				|| m_PreviousDirection == Direction::left && usePrevious == true)
			{
				sprite->SetRow(12);
			}
			else if (m_Direction == Direction::up && usePrevious == false
				|| m_PreviousDirection == Direction::up && usePrevious == true)
			{
				sprite->SetRow(0);
			}
			else if (m_Direction == Direction::down && usePrevious == false
				|| m_PreviousDirection == Direction::down && usePrevious == true)
			{
				sprite->SetRow(18);
			}
		}
	};

	class DigCommand : public Command
	{
	private:
		float m_DigSpeed = 30.0f;
	public:
		DigCommand(Direction direction) : Command{ direction } {}
		void Dig() {
			std::cout << "Dig" << std::endl;
		};
		virtual dae::State GetPlayerState() override { return dae::State::Digging; }
		virtual bool GetIsButton() override { return false; }
		virtual void execute(TransformComponent* transform, float elapsedTime) {
			Dig();
			Move(m_DigSpeed, elapsedTime, transform);
		}
		virtual void render(SpriteComponent* sprite, bool usePrevious)
		{
			sprite->SetColumn(2);
			if (m_Direction == Direction::right && usePrevious == false
				|| m_PreviousDirection == Direction::right && usePrevious == true)
			{
					sprite->SetRow(8);	
			}
			else if (m_Direction == Direction::left && usePrevious == false
				|| m_PreviousDirection == Direction::left && usePrevious == true)
			{
					sprite->SetRow(11);
			}
			else if (m_Direction == Direction::up && usePrevious == false
				|| m_PreviousDirection == Direction::up && usePrevious == true)
			{
					sprite->SetRow(1);
			}
			else if (m_Direction == Direction::down && usePrevious == false
				|| m_PreviousDirection == Direction::down && usePrevious == true)
			{
					sprite->SetRow(17);
			}
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
		virtual bool GetIsButton() override { return false; }
		virtual void execute(TransformComponent* transform, float elapsedTime) {
			Pump();
			UNREFERENCED_PARAMETER(elapsedTime);
			UNREFERENCED_PARAMETER(transform);
		}
		virtual void render(SpriteComponent* sprite, bool usePrevious)
		{
			UNREFERENCED_PARAMETER(usePrevious);
			sprite->SetRow(7);
		}
	};

	class IdleCommand : public Command
	{
	public:
		IdleCommand(Direction direction) : Command{ direction } {}
		virtual bool GetIsButton() override { return false; }
		virtual dae::State GetPlayerState() override { return dae::State::Idle; }
		virtual  void execute(TransformComponent* transform, float elapsedTime)
		{
			UNREFERENCED_PARAMETER(elapsedTime);
			UNREFERENCED_PARAMETER(transform);
		}
		virtual void render(SpriteComponent* sprite, bool usePrevious)
		{
			UNREFERENCED_PARAMETER(usePrevious);
			switch (m_Direction)
			{
			case Direction::right:
				sprite->SetRow(19);
				break;
			case Direction::left:
				sprite->SetRow(20);
				break;
			case Direction::up:
				sprite->SetRow(21);
				break;
			case Direction::down:
				sprite->SetRow(22);
				break;
			}
		}

	};

	class ButtonPressedCommand : public Command
	{
	public:
		ButtonPressedCommand() : Command{Direction::right} {}
		virtual bool GetIsButton() override { return true; }
		virtual dae::State GetPlayerState() override { return dae::State::Idle; }
		virtual void execute(TransformComponent* transform, float elapsedTime)
		{
			UNREFERENCED_PARAMETER(elapsedTime);
			UNREFERENCED_PARAMETER(transform);
		}
		virtual void  render(SpriteComponent* sprite, bool usePrevious)
		{
			UNREFERENCED_PARAMETER(usePrevious);
			UNREFERENCED_PARAMETER(sprite);
		}
	};
}

