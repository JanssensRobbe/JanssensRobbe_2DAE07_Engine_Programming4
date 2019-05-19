#include "MiniginPCH.h"
#include "InputManager.h"
#pragma comment (lib, "xinput.lib")
#include <SDL.h>

PBYTE dae::InputManager::m_pCurrKeyboardState = nullptr;
PBYTE dae::InputManager::m_pOldKeyboardState = nullptr;
PBYTE dae::InputManager::m_pKeyboardState0 = nullptr;
PBYTE dae::InputManager::m_pKeyboardState1 = nullptr;
bool dae::InputManager::m_KeyboardState0Active = true;
 XINPUT_STATE dae::InputManager::m_GamePadInputState[XUSER_MAX_COUNT];
 XINPUT_GAMEPAD dae::InputManager::m_Controller[XUSER_MAX_COUNT];
bool dae::InputManager::m_ConnectedGamepads[XUSER_MAX_COUNT];

dae::InputManager::~InputManager()
{

	for (auto actions : m_InputActions)
	{
		delete actions.second.Command;
	}
	if (m_pKeyboardState0 != nullptr)
	{
		delete[] m_pKeyboardState0;
		delete[] m_pKeyboardState1;

		m_pKeyboardState0 = nullptr;
		m_pKeyboardState1 = nullptr;
		m_pCurrKeyboardState = nullptr;
		m_pOldKeyboardState = nullptr;
	}
}
void dae::InputManager::Initialize()
{
	//Static Initialize Check
	//Pre-Object Initializations should happen before this check!
	for (int i{}; i < XUSER_MAX_COUNT; i++)
	{
		m_LastDirection[i] = dae::Direction::right;
	}
	if (m_IsInit)
		return;

	m_pKeyboardState0 = new BYTE[256];
	m_pKeyboardState1 = new BYTE[256];

	GetKeyboardState(m_pCurrKeyboardState);
	GetKeyboardState(m_pKeyboardState1);

	RefreshControllerConnections();
	m_IsInit = true;
}

void dae::InputManager::RefreshControllerConnections()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		const DWORD dwResult = XInputGetState(i, &state);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}

bool dae::InputManager::ProcessInput()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		ZeroMemory(&m_GamePadInputState[i], sizeof(XINPUT_STATE));
		XInputGetState(0, &m_GamePadInputState[i]);
	}

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

dae::Command* dae::InputManager::handleInput(dae::GamepadIndex playerIndex)
{
	for (auto it = m_InputActions.begin(); it != m_InputActions.end(); ++it)
	{
		if (it->second.PlayerIndex == playerIndex)
		{
			if (it->second.IsTriggered)
			{
				if (it->second.Command->GetPlayerState() == dae::State::Pumping)
					return new PumpCommand{ m_LastDirection[playerIndex]};
				m_LastDirection[playerIndex] = it->second.Command->getPlayerDirection();
				if (m_IsDigging && it->second.Command->GetPlayerState() == dae::State::Walking)
					return new DigCommand{ it->second.Command->getPlayerDirection() };
				return it->second.Command;
			}
		}
	}
	return new IdleCommand{ m_LastDirection[playerIndex] };
}

void dae::InputManager::Update()
{
	UpdateControllers();
	UpdateKeyboardStates();

	for (auto it = m_InputActions.begin(); it != m_InputActions.end(); ++it)
	{
		auto currAction = &(it->second);
		currAction->IsTriggered = false;

		//KEYBOARD
		if (IsKeyBoardDown(currAction->KeyboardCode, true) && IsKeyBoardDown(currAction->KeyboardCode))
			currAction->IsTriggered = true;


		//GAMEPADS
		if (!currAction->IsTriggered && currAction->GamepadButtonCode != 0)
			if (IsGamepadButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex) && IsGamepadButtonDown(currAction->GamepadButtonCode, currAction->PlayerIndex))
				currAction->IsTriggered = true;

	}
}

bool dae::InputManager::IsGamepadButtonDown(WORD button, GamepadIndex playerIndex)
{
	if (button > 0x0000 && button <= 0x8000)
	{
		if (!m_ConnectedGamepads[playerIndex])
			return false;
		return (m_GamePadInputState[playerIndex].Gamepad.wButtons& button) != 0;
	}

	return false;
}

bool dae::InputManager::IsKeyBoardDown(int key, bool previousFrame)
{
	if (previousFrame)
		return (m_pOldKeyboardState[key] & 0xF0) != 0;
	else
		return (m_pCurrKeyboardState[key] & 0xF0) != 0;
}

void dae::InputManager::UpdateControllers()
{
	for (DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
	{
		if (!m_ConnectedGamepads[i])
			return;

		//m_OldGamepadState[i] = m_CurrGamepadState[i];

		const DWORD dwResult = XInputGetState(i, &m_GamePadInputState[i]);
		m_ConnectedGamepads[i] = (dwResult == ERROR_SUCCESS);
	}
}

void dae::InputManager::UpdateKeyboardStates()
{
	BOOL getKeyboardResult;
	if (m_KeyboardState0Active)
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardState1);
		m_pOldKeyboardState = m_pKeyboardState0;
		m_pCurrKeyboardState = m_pKeyboardState1;
	}
	else
	{
		getKeyboardResult = GetKeyboardState(m_pKeyboardState0);
		m_pOldKeyboardState = m_pKeyboardState1;
		m_pCurrKeyboardState = m_pKeyboardState0;
	}

	m_KeyboardState0Active = !m_KeyboardState0Active;

}

void dae::InputManager::SetIsDigging(bool isDigging)
{
	m_IsDigging = isDigging;
}