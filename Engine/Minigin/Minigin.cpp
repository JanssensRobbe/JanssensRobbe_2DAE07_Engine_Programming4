#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextComponent.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "CharacterComponent.h"
#include "Level.h"

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		672,
		864,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/*Code constructing the scene world starts here*/
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto to = std::make_shared<GameObject>();
	LevelComponent* LevelComp = new LevelComponent();
	to->AddComponent(LevelComp);
	to->SetPosition(0, 0, 0);
	scene.Add(to);

	to = std::make_shared<GameObject>();
	TextComponent* TextComp2 = new TextComponent{"",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), true};
	to->AddComponent(TextComp2);
	to->SetPosition(630, 0, 0);
	scene.Add(to);


	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp5 = new SpriteComponent{"DigDug.png",2,1,0.2f,16.0f,8,3.0f };
	to->AddComponent(SpriteComp5);
	CharacterComponent* Character1 = new CharacterComponent{0, *SpriteComp5 };
	to->AddComponent(Character1);
	scene.Add(to);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		bool doContinue = true;
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			
			doContinue = input.ProcessInput();

			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
		}
	}

	Cleanup();
}
