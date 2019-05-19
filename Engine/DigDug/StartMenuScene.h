#pragma once
#include "Scene.h"
namespace dae {
	class StartMenuScene : public Scene
	{
	public:
		StartMenuScene(const std::string& name);
		virtual ~StartMenuScene() = default;

		void LoadScene() override;

		virtual void Update(float deltaTime) override;
		StartMenuScene(const StartMenuScene& other) = delete;
		StartMenuScene(StartMenuScene&& other) = delete;
		StartMenuScene& operator=(const StartMenuScene& other) = delete;
		StartMenuScene& operator=(StartMenuScene&& other) = delete;
	};
}

