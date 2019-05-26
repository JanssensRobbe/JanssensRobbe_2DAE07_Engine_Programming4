#pragma once
#include "Singleton.h"
#include "./../DigDug/ButtonComponent.h"

namespace dae {
	class ButtonManager : public Singleton<ButtonManager>
	{
	public:
		ButtonManager();
		~ButtonManager() = default;
		

		ButtonComponent& GetActiveButton() 
		{
			for (auto button : m_Buttons)
			{
				if (button->GetButtionActive())
					return (*button);
			}
			return (*m_Buttons[0]);
		}
		void SetNextButtonActive()
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
		void SetPreviousButtonActive() 
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
		void AddButton(ButtonComponent& button) { m_Buttons.push_back(&button); }
		void Update(float deltaTime)
		{
			if(m_IsSwapped)
				m_CoolDownButtonswap -= deltaTime;

			if (m_CoolDownButtonswap < 0.0f)
			{
				m_CoolDownButtonswap = 0.3f;
				m_IsSwapped = false;
			}

		}
	private:
		std::vector<ButtonComponent*> m_Buttons;
		int m_ActiveButton;
		bool m_IsSwapped = false;
		float m_CoolDownButtonswap = 0.3f;
	};
}

