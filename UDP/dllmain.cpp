#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "UDP.h"

//When the meme wants to be unleashed
void inject() {
	//Give it a console, cause that's what ceanko does
	AllocConsole();
	SetConsoleCtrlHandler(NULL, true);
	FILE* fIn;
	FILE* fOut;
	freopen_s(&fIn, "conin$", "r", stdin);
	freopen_s(&fOut, "conout$", "w", stdout);
	freopen_s(&fOut, "conout$", "w", stderr);

	std::cout << "Injection Successful!" << std::endl;

	//This is where the shitty magic happens
	new UDP();
}

//It's needed, just leave it
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)inject, nullptr, 0, nullptr);
	return TRUE;
}