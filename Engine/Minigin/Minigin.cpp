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
		640,
		480,
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

	auto go = std::make_shared<GameObject>();
	TextureComponent* TextureComp = new TextureComponent{ "background.jpg" };
	go->AddComponent(TextureComp);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	TextureComponent* TextureComp2 = new TextureComponent{ "logo.png" };
	go->AddComponent(TextureComp2);
	go->SetPosition(216, 180,0);
	scene.Add(go);

	auto to = std::make_shared<GameObject>();
	TextComponent* TextComp = new TextComponent{ "Programming 4 Assignment",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36)};
	to->AddComponent(TextComp);
	to->SetPosition(80, 20,0);
	scene.Add(to);

	to = std::make_shared<GameObject>();
	TextComponent* TextComp2 = new TextComponent{"",ResourceManager::GetInstance().LoadFont("Lingua.otf", 36), true};
	to->AddComponent(TextComp2);
	to->SetPosition(580, 0, 0);
	scene.Add(to);

	to = std::make_shared<GameObject>();
	SpriteComponent* SpriteComp = new SpriteComponent{ "TestSprite.png",Vector2f{0.0f,0.0f},4,2,1.0f};
	to->AddComponent(SpriteComp);
	to->SetPosition(200, 200, 0);
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
			if (input.handleInput() != nullptr)
				input.handleInput()->execute();

			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
		}
	}

	Cleanup();
}
