#pragma once
#include "Singleton.h"

namespace dae
{
	enum class SceneType {
		OnePlayerScene,
		StartMenu,
		None
	};
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name, SceneType type);

		void Update(float deltaTime);
		void Render();
		Scene& GetActiveScene();
	private:
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};

}
