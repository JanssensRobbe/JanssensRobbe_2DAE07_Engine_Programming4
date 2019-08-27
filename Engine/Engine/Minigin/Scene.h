#pragma once
#include "SceneManager.h"
#include "Structs.h"
#include "command.h"
#include <iostream>
#include <vector>

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
		Scene(const std::string& name);
		virtual ~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		std::string GetName() { return m_Name; }
		bool GetIsLoaded() { return m_IsLoaded; }

	protected:

		std::string m_Name{};
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};
		std::vector<Point2f> m_PlayerPositions;
		static unsigned int idCounter;
		bool m_IsLoaded = false;
	};

}
