#include "pch.h"
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
#include "StartMenuScene.h"
#include "ButtonManager.h"
#include "Level.h"
#include "Locator.h"

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

	srand(UINT(time(NULL)));

	Renderer::GetInstance().Init(window);
}

/*Code constructing the scene world starts here*/
void dae::Minigin::LoadGame() const
{
	auto scene = SceneManager::GetInstance().CreateScene(SceneType::StartMenu,std::make_shared<StartMenuScene>("MainMenu"));
	SceneManager::GetInstance().SetActiveScene(scene);
	scene->LoadScene();
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

		input.Initialize();
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			
			doContinue = input.ProcessInput();
			input.Update();
			sceneManager.Update(deltaTime);
			renderer.Render();
			lastTime = currentTime;
			if(!SceneManager::GetInstance().GetActiveScene()->GetIsLoaded())
				SceneManager::GetInstance().GetActiveScene()->LoadScene();
		}
	}

	Cleanup();
}
