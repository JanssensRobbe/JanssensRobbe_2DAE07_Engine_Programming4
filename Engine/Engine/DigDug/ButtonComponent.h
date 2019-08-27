#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "TextureComponent.h"
#include "SceneManager.h"

namespace dae {
	class ButtonComponent :public BaseComponent
	{
	public:
		ButtonComponent(Rectf destRect, std::string texture);
		~ButtonComponent()
		{
			delete m_pTexture;
		};

		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		void SetLoadedScene(std::string name, SceneType scene);
		void SetSceneLoaded(bool isLoaded) { m_LoadScene = isLoaded; }
		void SetButtonActive(bool isActive) { m_ActiveButton = isActive; }
		bool GetButtionActive() { return m_ActiveButton; }
		ButtonComponent(const ButtonComponent& other) = delete;
		ButtonComponent(ButtonComponent&& other) noexcept = delete;
		ButtonComponent& operator=(const ButtonComponent& other) = delete;
		ButtonComponent& operator=(ButtonComponent&& other) noexcept = delete;
	private:
		Rectf m_DestRect;
		bool m_ActiveButton = false;
		bool m_LoadScene = false;
		SceneType m_SceneType;
		TextureComponent* m_pTexture;
		std::shared_ptr<Scene> m_Scene;
	};
}
