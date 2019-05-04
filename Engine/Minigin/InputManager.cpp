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

std::shared_ptr<dae::Command> dae::InputManager::handleInput()
{
	switch (m_State)
	{
	case dae::GameState::MainMenu:
		return handleMainMenuInput();
		break;
	case dae::GameState::OnePlayer:
		return handleOnePlayerInput();
		break;
	default:
		return std::make_shared<IdleCommand>(Direction::right);
		break;
	}

}

std::shared_ptr<dae::Command> dae::InputManager::handleMainMenuInput()
{
	auto buttonA_ = std::make_shared<ButtonPressedCommand>();
	if (IsPressed(ControllerButton::ButtonA)) return buttonA_;

	return std::make_shared<IdleCommand>(Direction::right);
}

std::shared_ptr<dae::Command> dae::InputManager::handleOnePlayerInput()
{
	auto buttonX_ = std::make_shared<PumpCommand>(dae::Direction::right);

	auto buttonRightWalking_ = std::make_shared < WalkCommand>(dae::Direction::right);
	auto buttonLeftWalking_ = std::make_shared < WalkCommand>(dae::Direction::left);
	auto buttonUpWalking_ = std::make_shared < WalkCommand>(dae::Direction::up);
	auto buttonDownWalking_ = std::make_shared < WalkCommand>(dae::Direction::down);

	auto buttonRightDigging_ = std::make_shared <DigCommand>(dae::Direction::right);
	auto buttonLeftDigging_ = std::make_shared <DigCommand>(dae::Direction::left);
	auto buttonUpDigging_ = std::make_shared <DigCommand>(dae::Direction::up);
	auto buttonDownDigging_ = std::make_shared <DigCommand>(dae::Direction::down);
	auto idleCommand = std::make_shared <IdleCommand>(m_LastDirection);

	if (IsPressed(ControllerButton::ButtonX)) return buttonX_;
	if (!m_IsDigging)
	{
		if (IsPressed(ControllerButton::LeftArrow))
		{
			m_LastDirection = Direction::left;
			return buttonLeftWalking_;
		}
		if (IsPressed(ControllerButton::RightArrow))
		{
			m_LastDirection = Direction::right;
			return buttonRightWalking_;
		}
		if (IsPressed(ControllerButton::UpArrow))
		{
			m_LastDirection = Direction::up;
			return buttonUpWalking_;
		}
		if (IsPressed(ControllerButton::DownArrow))
		{
			m_LastDirection = Direction::down;
			return buttonDownWalking_;
		}
	}
	else
	{
		if (IsPressed(ControllerButton::LeftArrow))
		{
			m_LastDirection = Direction::left;
			return buttonLeftDigging_;
		}
		if (IsPressed(ControllerButton::RightArrow))
		{
			m_LastDirection = Direction::right;
			return buttonRightDigging_;
		}
		if (IsPressed(ControllerButton::UpArrow))
		{
			m_LastDirection = Direction::up;
			return buttonUpDigging_;
		}
		if (IsPressed(ControllerButton::DownArrow))
		{
			m_LastDirection = Direction::down;
			return buttonDownDigging_;
		}
	}

	// Nothing pressed, so do nothing.
	return idleCommand;
}

void dae::InputManager::SetIsDigging(bool isDigging)
{
	m_IsDigging = isDigging;
}

void dae::InputManager::SetGameState(GameState state)
{
	m_State = state;
}