#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "TextureComponent.h"
#include "SceneManager.h"

namespace dae {
	class ButtonComponent :public BaseComponent
	{
	public:
		ButtonComponent(Rectf destRect, TextureComponent& texture);
		virtual ~ButtonComponent() = default;

		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		void SetLoadedScene(std::string name, SceneType scene);
		ButtonComponent(const ButtonComponent& other) = delete;
		ButtonComponent(ButtonComponent&& other) noexcept = delete;
		ButtonComponent& operator=(const ButtonComponent& other) = delete;
		ButtonComponent& operator=(ButtonComponent&& other) noexcept = delete;
	private:
		Rectf m_DestRect;
		bool m_ActiveButton;
		bool m_LoadScene;
		std::string m_SceneName;
		SceneType m_SceneType;
		TextureComponent* m_pTexture;
	};
}

