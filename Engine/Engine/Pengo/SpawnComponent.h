#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "SceneManager.h"
#include "TextureComponent.h"

namespace dae
{
	class Scene;
	class SpawnComponent :public BaseComponent
	{
	public:
		SpawnComponent();
		virtual ~SpawnComponent()
		{
			delete m_pTexture;
		}

		SpawnComponent(const SpawnComponent& other) = delete;
		SpawnComponent(SpawnComponent&& other) noexcept = delete;
		SpawnComponent& operator=(const SpawnComponent& other) = delete;
		SpawnComponent& operator=(SpawnComponent&& other) noexcept = delete;

		virtual void Update(float) override;
		virtual void Render() override;
		void SetCount(int count) { m_Count = count; }
		void SetAmount(int amount) { m_Amount = amount - m_Count; }
		void SpawnPlayer(std::shared_ptr<GameObject>& obj,std::string SpritePath, int nbCols, int nbRows, float frameSec, float frameSize, int startRow, float scale,
			std::string HealthTexturePath, int playerindex, Point2f healthPosition, int health,
			Point2f position, SceneType endscreenType);
		void SpawnSnobee(std::shared_ptr<GameObject>& obj, std::string EnemiesPath, int nrRows, int nrCols, float frameSec, float frameSize, float scale,
			int gridSize, int agentIndex, int NbColsMap, Point2f pos);
	private:
		float m_EnemySpawnTimer = 0.0f;
		float m_EnemySpawnCooldown = 15.0f;
		bool m_IsSpawning = true;
		TextureComponent* m_pTexture;
		int m_Count = 0;
		int m_Amount = 0;
	};
}

