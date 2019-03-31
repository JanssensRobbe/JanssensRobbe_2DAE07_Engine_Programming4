#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent
	{
	public:
		virtual void Update(float deltaTime) override;
		virtual void Render() override;

		void SetText(const std::string& text);


		explicit TextComponent(const std::string& text, std::shared_ptr<Font> font, bool IsFpsCountOn = false);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
	private:
		bool m_NeedsUpdate;
		bool m_IsFpsOn;
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		int m_FpsCount;
	};

}
