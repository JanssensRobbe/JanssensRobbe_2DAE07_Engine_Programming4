#include "MiniginPCH.h"
#include "InputManager.h"
#pragma comment (lib, "xinput.lib")
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&m_InputState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_InputState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	if (m_InputState.Gamepad.wButtons == int(button))
	{
		return true;
	}
	return false;
}

dae::Command* dae::InputManager::handleInput()
{
	FireCommand* buttonX_ = new FireCommand{};
	DuckCommand* buttonY_ = new DuckCommand{};
	FartCommand* buttonA_ = new FartCommand{};
	JumpCommand* buttonB_ = new JumpCommand{};

	if (IsPressed(ControllerButton::ButtonX)) return buttonX_;
	if (IsPressed(ControllerButton::ButtonY)) return buttonY_;
	if (IsPressed(ControllerButton::ButtonA)) return buttonA_;
	if (IsPressed(ControllerButton::ButtonB)) return buttonB_;

	// Nothing pressed, so do nothing.
	return NULL;
}