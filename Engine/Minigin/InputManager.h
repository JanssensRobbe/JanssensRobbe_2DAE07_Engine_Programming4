#pragma once
#include "windows.h"
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <map>

namespace dae
{
	enum GamepadIndex : DWORD
	{
		PlayerOne = 0,
		PlayerTwo = 1,
		PlayerThree = 2,
		PlayerFour = 3
	};

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

	enum InputTriggerState
	{
		Pressed,
		Released,
		Down
	};

	struct InputAction
	{
		InputAction() :
		ActionID(-1),
		Command(std::make_shared<IdleCommand>()),
		//TriggerState(Pressed),
		KeyboardCode(-1),
		MouseButtonCode(-1),
		GamepadButtonCode(0),
		PlayerIndex(PlayerOne),
		IsTriggered(false) {}

		InputAction(int actionID, std::shared_ptr<Command> command,/*InputTriggerState triggerState = Pressed,*/ int keyboardCode = -1, int mouseButtonCode = -1, WORD gamepadButtonCode = 0, GamepadIndex playerIndex = GamepadIndex::PlayerOne) :
		ActionID(actionID),
		//TriggerState(triggerState),
		Command(command),
		KeyboardCode(keyboardCode),
		MouseButtonCode(mouseButtonCode),
		GamepadButtonCode(gamepadButtonCode),
		PlayerIndex(playerIndex),
		IsTriggered(false) {}

	int ActionID;
	std::shared_ptr<Command> Command;
	//InputTriggerState TriggerState;
	int KeyboardCode; //VK_... (Range 0x07 <> 0xFE)
	int MouseButtonCode; //VK_... (Range 0x00 <> 0x06)
	WORD GamepadButtonCode; //XINPUT_GAMEPAD_...
	GamepadIndex PlayerIndex;
	
	bool IsTriggered;
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput();
		std::shared_ptr<dae::Command> handleInput(dae::GamepadIndex playerIndex = dae::PlayerOne);
		void Update();
		void Initialize();
		bool AddAction(InputAction action);

		bool IsActionTriggered(int actionID)
		{
			return m_InputActions[actionID].IsTriggered;
		}

		void ResetActions() {
			m_InputActions.clear();
		}
		void RefreshControllerConnections();
		bool IsGamepadButtonDown(WORD button, GamepadIndex playerIndex);
		bool IsKeyBoardDown(int key, bool previousFrame = false);
	private:
		
		//functions
		void UpdateControllers();
		void UpdateKeyboardStates();
		//member var
		static BYTE *m_pCurrKeyboardState, *m_pOldKeyboardState, *m_pKeyboardState0, *m_pKeyboardState1;
		static bool m_KeyboardState0Active;
		static XINPUT_STATE m_GamePadInputState[XUSER_MAX_COUNT];
		static XINPUT_GAMEPAD m_Controller[XUSER_MAX_COUNT];
		bool m_IsInit = false;
		std::map<int, InputAction> m_InputActions;
		static bool m_ConnectedGamepads[XUSER_MAX_COUNT];
	};
}
