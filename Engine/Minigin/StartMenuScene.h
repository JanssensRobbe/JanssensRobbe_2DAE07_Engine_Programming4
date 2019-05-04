#pragma once
#include "Scene.h"
namespace dae {
	class StartMenuScene : public Scene
	{
	public:
		StartMenuScene(const std::string& name);
		~StartMenuScene();

		void LoadScene() override;
		StartMenuScene(const StartMenuScene& other) = delete;
		StartMenuScene(StartMenuScene&& other) = delete;
		StartMenuScene& operator=(const StartMenuScene& other) = delete;
		StartMenuScene& operator=(StartMenuScene&& other) = delete;
	};
}

