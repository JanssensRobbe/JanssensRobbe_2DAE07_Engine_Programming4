#include "MiniginPCH.h"
#include "StartMenuScene.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "InputManager.h"
#include "ButtonComponent.h"


dae::StartMenuScene::StartMenuScene(const std::string& name)
	:Scene{name}
{
}


dae::StartMenuScene::~StartMenuScene()
{
}


void dae::StartMenuScene::LoadScene()
{
	InputManager::GetInstance().SetGameState(GameState::MainMenu);
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
	TextureComponent* ButtonTexComp = new TextureComponent{"Button.png"};
	to->AddComponent(ButtonTexComp);
	ButtonComponent* buttonComp = new ButtonComponent(Rectf{200,300,50,200},*ButtonTexComp);
	buttonComp->SetLoadedScene("OnePlayer",SceneType::OnePlayerScene);
	to->AddComponent(buttonComp);
	Add(to);
}

