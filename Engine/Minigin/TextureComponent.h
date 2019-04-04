#pragma once
#include "BaseComponent.h"
#include "Structs.h"
namespace dae
{
	class TextureComponent :public BaseComponent
	{
	public:
		explicit TextureComponent(std::string fileName);
		virtual ~TextureComponent() = default;
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void SetTexture(const std::string& filename);

		void Render(Rectf destRect, Rectf srcRect) const;
	protected:
		 virtual void Update(float deltaTime) override;
		 virtual void Render() override;
		 
	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}

