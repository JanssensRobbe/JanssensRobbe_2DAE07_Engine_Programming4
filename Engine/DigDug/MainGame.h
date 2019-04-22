#pragma once
#include "../Minigin/Minigin.h"

namespace dae 
{ 
class MainGame : public Minigin
{
public:
	MainGame();
	virtual ~MainGame() = default;

	virtual void Initialize();
	virtual void LoadGame() const;
	virtual void Cleanup();
	virtual void Run();
};
}

