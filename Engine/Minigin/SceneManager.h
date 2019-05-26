#pragma once
#include "Singleton.h"
namespace dae
{
	enum class SceneType {
		OnePlayerScene,
		TwoPlayerScene,
		VersusScene,
		StartMenu,
		GameOverMenu,
		WinnerMenu,
		None
	};
	class Scene;
	class CharacterComponent;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		std::shared_ptr<Scene> CreateScene(SceneType type, std::shared_ptr<Scene> scene);

		void Update(float deltaTime);
		void Render();
		std::shared_ptr<Scene> GetActiveScene();
		void SetActiveScene(SceneType activeScene);
		void AddCharacter(CharacterComponent& character)
		{
			if (std::find(m_Characters.begin(), m_Characters.end(), &character) == m_Characters.end())
			{
				m_Characters.push_back(&character);
			}
		}

		CharacterComponent* GetCharacter(int index)
		{
			return m_Characters[index];
		}
		void SetBoundries(Rectf boundries) {m_Boundries = boundries;}
		Rectf GetBoundries() { return m_Boundries; }
	private:
		std::vector<std::pair<SceneType, std::shared_ptr<dae::Scene>>> m_Scenes;
		std::shared_ptr<Scene> m_ActiveScene;
		std::vector<CharacterComponent*> m_Characters;
		Rectf m_Boundries{ 0.0f,48.0f, 672.0f, 720.0f };
	};

}
