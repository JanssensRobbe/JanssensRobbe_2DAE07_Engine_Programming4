#pragma once
#include "Singleton.h"
namespace dae
{
	enum class SceneType {
		OnePlayerScene,
		TwoPlayerScene,
		VersusScene,
		StartMenu,
		None
	};
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<Scene> CreateScene(SceneType type, std::shared_ptr<Scene> scene);

		void Update(float deltaTime);
		void Render();
		std::shared_ptr<Scene> GetActiveScene();
		void SetActiveScene(SceneType activeScene);
	private:
		std::vector<std::pair<SceneType, std::shared_ptr<dae::Scene>>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
	};

}
