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
	PumpCommand* buttonX_ = new PumpCommand{dae::Direction::right};
	DigCommand* buttonB_ = new DigCommand{ dae::Direction::right };
	WalkCommand* buttonRightArrow_ = new WalkCommand{ dae::Direction::right };
	WalkCommand* buttonLeftArrow_ = new WalkCommand{ dae::Direction::left };
	WalkCommand* buttonUpArrow_ = new WalkCommand{ dae::Direction::up };
	WalkCommand* buttonDownArrow_ = new WalkCommand{ dae::Direction::down };

	if (IsPressed(ControllerButton::ButtonX)) return buttonX_;
	if (IsPressed(ControllerButton::ButtonB)) return buttonB_;
	if (IsPressed(ControllerButton::LeftArrow)) return buttonLeftArrow_;
	if (IsPressed(ControllerButton::RightArrow)) return buttonRightArrow_;
	if (IsPressed(ControllerButton::UpArrow)) return buttonUpArrow_;
	if (IsPressed(ControllerButton::DownArrow)) return buttonDownArrow_;

	// Nothing pressed, so do nothing.
	return NULL;
}