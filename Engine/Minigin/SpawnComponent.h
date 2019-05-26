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

		std::shared_ptr<GameObject>& SpawnPlayer(std::shared_ptr<GameObject> obj,std::string SpritePath, int nbCols, int nbRows, float frameSec, float frameSize, int startRow, float scale,
			std::string HealthTexturePath, int playerindex, Point2f healthPosition, int health,
			Point2f position, SceneType endscreenType);
		std::shared_ptr<GameObject>& SpawnPooka(std::shared_ptr<GameObject> obj);
		std::shared_ptr<GameObject>& SpawnFygar(std::shared_ptr<GameObject> obj);
	};
}

