#include "MiniginPCH.h"
#include "CharacterComponent.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"
#include "InputManager.h"
#include "Level.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Command.h"



dae::CharacterComponent::CharacterComponent(DWORD playerNumber, SpriteComponent& spriteComponent)
	:BaseComponent{}
	, m_PlayerNumber{playerNumber}
	, m_pSprite{&spriteComponent}
{
}