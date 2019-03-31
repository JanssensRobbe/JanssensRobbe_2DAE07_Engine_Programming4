#pragma once
#include <iostream>
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() {};
		virtual void execute() = 0;
	};

	class JumpCommand : public Command
	{
	public:
		void jump()
		{
			std::cout << "jump" << std::endl;
		}
		virtual void execute() { jump(); }
	};

	class FireCommand : public Command
	{
	public:
		void Fire()
		{
			std::cout << "Fire" << std::endl;
		}
		virtual void execute() { Fire(); }
	};

	class DuckCommand : public Command
	{
	public:
		void duck() {
			std::cout << "duck" << std::endl;
		};
		virtual void execute() { duck(); }
	};

	class FartCommand : public Command
	{
	public:
		void fart() {
			std::cout << "fart" << std::endl;
		};
		virtual void execute() { fart(); }
	};
}

