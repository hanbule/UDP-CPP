#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include "UDP.h"

//Function that's run when the thread below is created
void inject() {
	//Give it a console for debugging purposes
	AllocConsole();
	//Allow you to close the console without the host process closing too
	SetConsoleCtrlHandler(NULL, true);
	//Assign console in and out to pass to the create console rather than minecraft's
	FILE* fIn;
	FILE* fOut;
	freopen_s(&fIn, "conin$", "r", stdin);
	freopen_s(&fOut, "conout$", "w", stdout);
	freopen_s(&fOut, "conout$", "w", stderr);

	std::cout << "Injection Successful!" << std::endl;

	//This is where the shitty magic happens
	new UDP();
}

//DLL entry function, it's what gets called when you inject the DLL (also called for other reasons but that's not important)
BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	//If the reason of the call to this func is when the DLL attaches to the process
	if (fdwReason == DLL_PROCESS_ATTACH)
		//Create a thread running the 'inject' func
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)inject, nullptr, 0, nullptr);
	return TRUE;
}