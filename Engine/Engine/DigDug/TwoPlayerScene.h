#pragma once
#include "Scene.h"
namespace dae
{
	class TwoPlayerScene : public Scene
	{
	public:
		TwoPlayerScene(const std::string& name);
		 ~TwoPlayerScene();

		void LoadScene() override;
		TwoPlayerScene(const TwoPlayerScene& other) = delete;
		TwoPlayerScene(TwoPlayerScene&& other) = delete;
		TwoPlayerScene& operator=(TwoPlayerScene&& other) = delete;
	};
}

