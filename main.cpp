#include "GAME/WORLD/World.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {
	auto project = std::make_unique<World>();

	project->MainLoop();

	return 0;
}