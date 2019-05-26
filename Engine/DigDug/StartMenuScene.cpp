#include "pch.h"
#include "StartMenuScene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "InputManager.h"
#include "ButtonComponent.h"
#include "ButtonManager.h"


dae::StartMenuScene::StartMenuScene(const std::string& name)
	:Scene{name}
{
}


void dae::StartMenuScene::Update(float deltaTime)
{
	for (auto gameObject : m_Objects)
	{
		gameObject->Update(deltaTime);
	}
}

void dae::StartMenuScene::LoadScene()
{
	InputManager::GetInstance().ResetActions();
	auto ButtonPressedAction = InputAction{ 0,std::make_shared<ButtonPressedCommand>(),'K',-1,WORD(dae::ControllerButton::ButtonA),dae::PlayerOne };
	InputManager::GetInstance().AddAction(ButtonPressedAction);
	auto ButtonDownAction = InputAction{ 1,std::make_shared<DownCommand>(),'S',-1,WORD(dae::ControllerButton::DownArrow),dae::PlayerOne };
	InputManager::GetInstance().AddAction(ButtonDownAction);
	auto ButtonUpAction = InputAction{ 2, std::make_shared<UpCommand>(),'W',-1,WORD(dae::ControllerButton::UpArrow), dae::PlayerOne };
	InputManager::GetInstance().AddAction(ButtonUpAction);

	auto to = std::make_shared<GameObject>();
	TextureComponent* TexComp = new TextureComponent("MainMenu.png");
	to->AddComponent(TexComp);
	to->SetPosition(0, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	TextComponent* TextComp = new TextComponent("§", ResourceManager::GetInstance().LoadFont("DIG DUG.ttf", 90), {0,0,0});
	to->AddComponent(TextComp);
	to->SetPosition(190, 120);
	Add(to);

	to = std::make_shared<GameObject>();
	ButtonComponent* buttonComp = new ButtonComponent(Rectf{225,300,200,100},"Button1Player.png");
	buttonComp->SetLoadedScene("OnePlayer",SceneType::OnePlayerScene);
	buttonComp->SetButtonActive(true);
	ButtonManager::GetInstance().AddButton(*buttonComp);
	to->AddComponent(buttonComp);
	Add(to);

	to = std::make_shared<GameObject>();
	ButtonComponent* buttonComp2 = new ButtonComponent(Rectf{ 225,450,200,100 },"Button2Players.png");
	buttonComp2->SetLoadedScene("TwoPlayer", SceneType::TwoPlayerScene);
	ButtonManager::GetInstance().AddButton(*buttonComp2);
	to->AddComponent(buttonComp2);
	Add(to);

	to = std::make_shared<GameObject>();
	ButtonComponent* buttonComp3 = new ButtonComponent(Rectf{ 225,600,200,100 },"ButtonVersus.png");
	buttonComp3->SetLoadedScene("VersusPlayer", SceneType::VersusScene);
	ButtonManager::GetInstance().AddButton(*buttonComp3);
	to->AddComponent(buttonComp3);
	Add(to);
}

