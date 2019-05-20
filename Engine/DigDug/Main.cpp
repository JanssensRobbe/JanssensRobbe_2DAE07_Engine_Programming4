#include "pch.h"
#pragma comment(lib,"xinput.lib")

// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "SDL.h"
#include "Minigin.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	dae::Minigin engine;
	//_CrtSetBreakAlloc(1365);
	engine.Run();
	//_CrtDumpMemoryLeaks();
    return 0;
}

