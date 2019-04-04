#pragma once
#include "Singleton.h"
#include "Structs.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture,const Rectf destRect, const Rectf srcRect) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

