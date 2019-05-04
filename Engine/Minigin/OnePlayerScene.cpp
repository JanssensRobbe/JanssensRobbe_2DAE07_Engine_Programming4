#include "MiniginPCH.h"
#include "OnePlayerScene.h"
#include "Level.h"
#include "TextComponent.h"
#include "CharacterComponent.h"
#include "ResourceManager.h"
#include "InputManager.h"


dae::OnePlayerScene::OnePlayerScene(const std::string& name)
	:Scene{name}
{

}
dae::OnePlayerScene::~OnePlayerScene()
{

}

void dae::OnePlayerScene::LoadScene()
{
	InputManager::GetInstance().SetGameState(GameState::OnePlayer);
	auto to = std::make_shared<GameObject>();
	LevelComponent* LevelComp = new LevelComponent();
	to->AddComponent(LevelComp);
	to->SetPosition(0, 0);
	Add(to);

	to = std::make_shared<GameObject>();
	TextComponent* TextComp2 = new TextComponent{ "",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36),{255,255,255}, true };
	to->AddComponent(TextComp2);
	to->SetPosition(630, 0);
	Add(to);


	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp5 = new SpriteComponent{ "DigDug.png",2,1,0.2f,16.0f,8,3.0f };
	to->AddComponent(SpriteComp5);
	CharacterComponent* Character1 = new CharacterComponent{ 0, *SpriteComp5 };
	to->SetPosition(336, 432);
	to->AddComponent(Character1);
	Add(to);
}

