#include "MiniginPCH.h"
#include "ButtonManager.h"
#include "InputManager.h"

dae::ButtonManager::ButtonManager()
{
}

void dae::ButtonManager::Update(float deltaTime)
{
	m_Buttons = GetGameObject()->GetComponents<ButtonComponent>();
	auto command = InputManager::GetInstance().handleInput();
	if (command != std::shared_ptr<NullCommand>())
		command->execute((*GetGameObject()));
	for (auto button : m_Buttons)
	{
		button->Update(deltaTime);
	}

	if (m_IsSwapped)
		m_CoolDownButtonswap -= deltaTime;

	if (m_CoolDownButtonswap < 0.0f)
	{
		m_CoolDownButtonswap = 0.3f;
		m_IsSwapped = false;
	}
}

void dae::ButtonManager::Render()
{
	for (auto button : m_Buttons)
	{
		button->Render();
	}
}

void dae::ButtonManager::SetNextButtonActive()
{
	if (!m_IsSwapped)
	{
		m_IsSwapped = true;
		m_Buttons[m_ActiveButton]->SetButtonActive(false);
		if (m_ActiveButton == int(m_Buttons.size() - 1))
			m_ActiveButton = 0;
		else
			++m_ActiveButton;

		m_Buttons[m_ActiveButton]->SetButtonActive(true);
	}
}
void dae::ButtonManager::SetPreviousButtonActive()
{
	if (!m_IsSwapped)
	{
		m_IsSwapped = true;
		m_Buttons[m_ActiveButton]->SetButtonActive(false);
		if (m_ActiveButton == 0)
			m_ActiveButton = int(m_Buttons.size()) - 1;
		else
			--m_ActiveButton;

		m_Buttons[m_ActiveButton]->SetButtonActive(true);
	}
}
