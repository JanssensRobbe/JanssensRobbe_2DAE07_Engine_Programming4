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
		void SetRow(int row) { m_StartRow = row; }
		void SetColumn(int column) { m_Cols = column; }
		SpriteComponent(const std::string& fileName, int nrCols, int nrRows, float frameSec, float frameSize, int startRow = 0, float size = 1);
		virtual ~SpriteComponent();
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;
	private:
		const TextureComponent* m_pTexture;
		int m_Cols;
		const int m_Rows;
		float m_FrameSec;
		float m_AccuSec;
		int m_ActFrame;
		float m_FrameSize;
		int m_StartRow;
		float m_Size;
		int GetNrFrames() const;
	};
}

