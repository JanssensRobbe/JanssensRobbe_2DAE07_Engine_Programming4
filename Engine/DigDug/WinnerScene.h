#pragma once
#include "Scene.h"
namespace dae
{
	class WinnerScene :public Scene
	{
	public:
		WinnerScene(const std::string& name);
		~WinnerScene();

		void LoadScene() override;
		WinnerScene(const WinnerScene& other) = delete;
		WinnerScene(WinnerScene&& other) = delete;
		WinnerScene& operator=(const WinnerScene& other) = delete;
		WinnerScene& operator=(WinnerScene&& other) = delete;
	};
}

