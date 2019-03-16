#pragma once
#include "BaseComponent.h"
namespace dae
{
	class TextureComponent :public BaseComponent
	{
	public:
		explicit TextureComponent(SDL_Texture* texture);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void SetTexture(const std::string& filename);
	protected:
		 virtual void Update(float deltaTime) override;
		 virtual void Render() override;
	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}

