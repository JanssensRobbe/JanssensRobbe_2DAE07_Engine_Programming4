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
		std::shared_ptr<Scene> CreateScene(const std::string& name, SceneType type);

		void Update(float deltaTime);
		void Render();
		std::shared_ptr<Scene> GetActiveScene();
		void SetActiveScene(std::shared_ptr<Scene> activeScene);
	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
	};

}
