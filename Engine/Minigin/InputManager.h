#pragma once
#include "windows.h"
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		LeftArrow = XINPUT_GAMEPAD_DPAD_LEFT,
		RightArrow = XINPUT_GAMEPAD_DPAD_RIGHT,
		UpArrow = XINPUT_GAMEPAD_DPAD_UP,
		DownArrow = XINPUT_GAMEPAD_DPAD_DOWN
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		std::shared_ptr<dae::Command> handleInput();
		void SetIsDigging(bool isDigging);
		void SetCommand(ControllerButton button, std::shared_ptr<dae::Command> command)
		{
			m_Commands.push_back(std::make_pair(button,command));
		};

		void ResetCommands() {
			m_Commands.clear();
		}
	private:
		//member var
		XINPUT_STATE m_InputState{};
		XINPUT_GAMEPAD m_Controller{};
		bool m_IsDigging{};
		Direction m_LastDirection = Direction::right;
		bool IsPressed(ControllerButton button) const;
		std::vector<std::pair<ControllerButton, std::shared_ptr<dae::Command>>> m_Commands;
	};

}
