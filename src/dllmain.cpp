// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include <Windows.h>
#include "Evasion/Evade.h"

FILE* CreateConsole() {

    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    std::cout << "Initalizing evade...\n" << std::endl;

    return f;
}

void CleanUp(FILE* f, HMODULE hModule) {

    std::cout << "[*] Cleaning up..." << std::endl;

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
}

DWORD WINAPI Thread(HMODULE hModule) {

    // Init console
    FILE* f = CreateConsole();

    // Main Hack Loop
    hackLoop();

    // Cleanup stuff
    CleanUp(f, hModule);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        HANDLE hThread = nullptr;
        hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Thread, hModule, 0, nullptr);
        if (hThread) {
            CloseHandle(hThread);
        }
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}