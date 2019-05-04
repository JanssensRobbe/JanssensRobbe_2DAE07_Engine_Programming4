#pragma once
#include "BaseComponent.h"
#include "Structs.h"
#include "Command.h"
namespace dae
{
	class SpriteComponent;
	class TextureComponent;
	class CharacterComponent : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		CharacterComponent(int playerNumber, SpriteComponent& spriteComponent);
		virtual ~CharacterComponent() = default;
		CharacterComponent(const CharacterComponent& other) = delete;
		CharacterComponent(CharacterComponent&& other) = delete;
		CharacterComponent& operator=(const CharacterComponent& other) = delete;
		CharacterComponent& operator=(CharacterComponent&& other) = delete;

	private:
		SpriteComponent* m_pSprite;
		Direction m_HorizontalDirection, m_VerticalDirection;
		int m_PlayerNumber;
		float m_MovementSpeed;
		State m_PlayerState;
		Point2f m_PlayerPos;
		bool m_UsePreviousDirection;
		std::shared_ptr<Command> m_pCommand;
	};
}

