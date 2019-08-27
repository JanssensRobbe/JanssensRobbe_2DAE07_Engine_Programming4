#pragma once
#include "Scene.h"
namespace dae
{
	class VersusScene :public Scene
	{
	public:
		VersusScene(const std::string& name);
		~VersusScene();

		void LoadScene() override;
		VersusScene(const VersusScene& other) = delete;
		VersusScene(VersusScene&& other) = delete;
		VersusScene& operator=(VersusScene&& other) = delete;
	};
}

