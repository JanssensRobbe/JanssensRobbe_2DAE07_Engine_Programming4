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
		Command* handleInput();
		
	private:
		XINPUT_STATE m_InputState{};
		XINPUT_GAMEPAD m_Controller{};
		bool IsPressed(ControllerButton button) const;
	};

}
