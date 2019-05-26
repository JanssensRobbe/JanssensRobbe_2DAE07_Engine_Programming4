#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "SceneManager.h"
#include "Score.h"
namespace dae
{
	class SpriteComponent;
	class TextureComponent;
	class Command;
	class CharacterComponent : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) override = 0;
		virtual void Render() override = 0;

		virtual Direction GetDirection() = 0;
		virtual Point2f GetPosition() = 0;
		virtual bool GetIsDead() { return m_IsDead; }
		virtual void SetIsDigging(bool) = 0;
		SpriteComponent* GetSprite() { return m_pSprite; }
		DWORD GetPlayerNumber() { return m_PlayerNumber; }
		CharacterComponent(DWORD playerNumber, SpriteComponent& spriteComponent);
		~CharacterComponent();
		CharacterComponent(const CharacterComponent& other) = delete;
		CharacterComponent(CharacterComponent&& other) = delete;
		CharacterComponent& operator=(const CharacterComponent& other) = delete;
		CharacterComponent& operator=(CharacterComponent&& other) = delete;

	private:
		SpriteComponent* m_pSprite;
		DWORD m_PlayerNumber;
		bool m_IsDead = false;
	};
}

