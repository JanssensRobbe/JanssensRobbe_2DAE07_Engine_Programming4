#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "SceneManager.h"

namespace dae
{
	class SpawnComponent :public BaseComponent
	{
	public:
		SpawnComponent();
		virtual ~SpawnComponent() = default;

		SpawnComponent(const SpawnComponent& other) = delete;
		SpawnComponent(SpawnComponent&& other) noexcept = delete;
		SpawnComponent& operator=(const SpawnComponent& other) = delete;
		SpawnComponent& operator=(SpawnComponent&& other) noexcept = delete;

		virtual void Update(float) override {};
		virtual void Render() override {};

		void SpawnPlayer(std::shared_ptr<GameObject>& obj,std::string SpritePath, int nbCols, int nbRows, float frameSec, float frameSize, int startRow, float scale,
			std::string HealthTexturePath, int playerindex, Point2f healthPosition, int health,
			Point2f position, SceneType endscreenType);
		void SpawnPooka(std::shared_ptr<GameObject>& obj, std::string EnemiesPath, int nrRows, int nrCols, float frameSec, float frameSize, float scale,
			int MaxNrInflate, int gridSize, int NbColsMap, int agentIndex, Point2f pos);
		void SpawnFygar(std::shared_ptr<GameObject>& obj, std::string EnemiesPath, int nrRows, int nrCols, float frameSec, float frameSize, float scale,
			int MaxNrInflate, int gridSize, int NbColsMap, int agentIndex, Point2f pos);
	};
}

