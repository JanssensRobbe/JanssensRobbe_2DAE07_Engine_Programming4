#pragma once
#include "SceneManager.h"
#include "Structs.h"
#include "command.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name, SceneType type);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);

		void Update(float deltaTime);
		void Render() const;

		virtual void LoadScene() = 0;
		void SetPlayerPosition(Point2f position);
		Point2f GetPlayerPosition() { return m_PlayerPosition; }
		void SetPlayerDirection(dae::Direction direction) { m_PlayerDirection = direction; }
		dae::Direction GetPlayerDirection() { return m_PlayerDirection; }
		Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected: 
		
		std::string m_Name{};
		std::vector < std::shared_ptr<SceneObject>> m_Objects{};
		Point2f m_PlayerPosition;
		dae::Direction m_PlayerDirection;
		static unsigned int idCounter;
	};

}
