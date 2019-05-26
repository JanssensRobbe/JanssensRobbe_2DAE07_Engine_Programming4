#pragma once
#include "Scene.h"
namespace dae {
	class GameOverScene :public Scene
	{
	public:
		GameOverScene(const std::string& name);
		~GameOverScene();

		void LoadScene() override;
		GameOverScene(const GameOverScene& other) = delete;
		GameOverScene(GameOverScene&& other) = delete;
		GameOverScene& operator=(const GameOverScene& other) = delete;
		GameOverScene& operator=(GameOverScene&& other) = delete;
	};
}

