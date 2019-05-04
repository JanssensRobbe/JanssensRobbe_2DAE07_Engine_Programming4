#pragma once
#include "Scene.h"

namespace dae
{
	class OnePlayerScene : public Scene
	{
	public:
		OnePlayerScene(const std::string& name);
		~OnePlayerScene();

		void LoadScene() override;
		OnePlayerScene(const OnePlayerScene& other) = delete;
		OnePlayerScene(OnePlayerScene&& other) = delete;
		OnePlayerScene& operator=(const OnePlayerScene& other) = delete;
		OnePlayerScene& operator=(OnePlayerScene&& other) = delete;	
	};
}

