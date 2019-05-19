#pragma once
#include "Scene.h"
namespace dae
{
	class TwoPlayerScene : public Scene
	{
	public:
		TwoPlayerScene(const std::string& name);
		virtual ~TwoPlayerScene() = default;

		void LoadScene() override;
		TwoPlayerScene(const TwoPlayerScene& other) = delete;
		TwoPlayerScene(TwoPlayerScene&& other) = delete;
		TwoPlayerScene& operator=(TwoPlayerScene&& other) = delete;
	};
}

