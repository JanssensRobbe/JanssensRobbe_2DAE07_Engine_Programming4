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
	return (m_InputState.Gamepad.wButtons & static_cast<WORD>(button)) != 0;
}

std::shared_ptr<dae::Command> dae::InputManager::handleInput()
{
	for (auto command : m_Commands)
	{
		if (IsPressed(command.first) && command.second->GetPlayerState() == dae::State::Walking)
		{
			m_LastDirection = command.second->getPlayerDirection();
			if (m_IsDigging)
				return std::make_shared<DigCommand>(command.second->getPlayerDirection());
			return command.second;
		}
		else if (IsPressed(command.first) && command.second->GetPlayerState() == dae::State::Pumping)
			return std::make_shared<PumpCommand>(m_LastDirection);
		else if(IsPressed(command.first))
			return command.second;

	}
	return  std::make_shared<IdleCommand>(m_LastDirection);

}

void dae::InputManager::SetIsDigging(bool isDigging)
{
	m_IsDigging = isDigging;
}