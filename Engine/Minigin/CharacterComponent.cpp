#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "SpriteComponent.h"
#include "InputManager.h"


dae::CharacterComponent::CharacterComponent(int playerNumber, SpriteComponent& spriteComponent)
	:BaseComponent{}
	, m_PlayerNumber{playerNumber}
	, m_pSprite{&spriteComponent}
	, m_PlayerState{dae::State::Idle}
{
}


void dae::CharacterComponent::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	auto command = InputManager::GetInstance().handleInput();
	if (command != NULL)
	{
		m_PlayerState = command->GetPlayerState();
		command->execute(GetTransform(),elapsedTime);
	}
	else
	{
		m_PlayerState = dae::State::Idle;
	}


}

void dae::CharacterComponent::Render()
{
	if (m_PlayerState == dae::State::Idle)
	{
		m_pSprite->SetRow(19);
		m_pSprite->SetColumn(2);
	}
	else
	{
		auto command = InputManager::GetInstance().handleInput();
		command->render(m_pSprite);
	}
}