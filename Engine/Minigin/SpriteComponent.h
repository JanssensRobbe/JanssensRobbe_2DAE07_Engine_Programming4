#pragma once
#include "BaseComponent.h"
#include "Vector2f.h"
#include "TextureComponent.h"

namespace dae {
	class SpriteComponent : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		SpriteComponent(const std::string& fileName, const Vector2f& displacement, int nrCols, int nrRows, float frameSec);
		virtual ~SpriteComponent();
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;
	private:
		const TextureComponent* m_pTexture;
		Vector2f m_Displacement;
		const int m_Cols;
		const int m_Rows;
		float m_FrameSec;
		float m_AccuSec;
		int m_ActFrame;

		int GetNrFrames() const;
	};
}

