#pragma once
#include "SceneManager.h"
#include "Structs.h"
#include "command.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend std::shared_ptr<dae::Scene> SceneManager::CreateScene(SceneType type, std::shared_ptr<Scene> scene);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		virtual void Update(float deltaTime);
		virtual void Render() const;

		virtual void LoadScene() = 0;
		void SetPlayerPosition(Point2f position, int index);
		std::vector<Point2f> GetPlayerPositions() { return m_PlayerPositions; }
		void SetPlayerDirection(dae::Direction direction) { m_PlayerDirection = direction; }
		dae::Direction GetPlayerDirection() { return m_PlayerDirection; }
		Scene(const std::string& name);
		virtual ~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:

		std::string m_Name{};
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};
		std::vector<Point2f> m_PlayerPositions;
		dae::Direction m_PlayerDirection;
		static unsigned int idCounter;
	};

}
