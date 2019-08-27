#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void Render() override;
		virtual void Render(Point2f position);

		void SetText(const std::string& text);
		void DisableNormalRender(bool state) { m_IsNormalRenderDisabled = state; }

		explicit TextComponent(const std::string& text, std::shared_ptr<Font> font, SDL_Color color = {255,255,255}, bool IsFpsCountOn = false);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		bool m_IsFpsOn;
		bool m_IsNormalRenderDisabled = false;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		int m_FpsCount;
		SDL_Color m_Color;
	};

}
