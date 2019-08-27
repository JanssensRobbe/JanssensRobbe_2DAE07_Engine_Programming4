#pragma once
#include "./../Pengo/ButtonComponent.h"
#include "BaseComponent.h"

namespace dae {
	class ButtonManager : public BaseComponent
	{
	public:
		ButtonManager();
		~ButtonManager()
		{
			m_Buttons.clear();
		}
		
		ButtonManager(const ButtonManager& other) = delete;
		ButtonManager(ButtonManager&& other) noexcept = delete;
		ButtonManager& operator=(const ButtonManager& other) = delete;
		ButtonManager& operator=(ButtonManager&& other) noexcept = delete;

		ButtonComponent* GetActiveButton() 
		{
			for (auto button : m_Buttons)
			{
				if (button->GetButtionActive())
					return button;
			}
			return m_Buttons[0];
		}
		void SetNextButtonActive();
		void SetPreviousButtonActive();
		void AddButton(ButtonComponent& button) { m_Buttons.push_back(&button); }
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

	private:
		std::vector<ButtonComponent*> m_Buttons;
		int m_ActiveButton;
		bool m_IsSwapped = false;
		float m_CoolDownButtonswap = 0.3f;
	};
}

