#include <iostream>
#include <Windows.h>
#include "Evade.h"
#include "../haze/haze.hpp"

struct Vars {
	uintptr_t module;
	uintptr_t localPlayer;
}Addrs;

// Address handling
// ================================================================================================================
void GetModule() {
	Addrs.module = (uintptr_t)GetModuleHandle("client_panorama.dll");
	std::cout << "[+] Found Module Address (client_panorama.dll) -> 0x" << std::hex << Addrs.module << std::endl;
}

void GetLocalPlayer() {
	if (Addrs.localPlayer == NULL) {
		do {
			Addrs.localPlayer = *(uintptr_t*)(Addrs.module + hazedumper::signatures::dwLocalPlayer);
			Sleep(500);
		} while (Addrs.localPlayer == NULL);
	}
	std::cout << "[+] Found LocalPlayer PTR -> 0x" << std::hex << Addrs.localPlayer << std::endl;
}

void HealthTest() {
	int health = *(int*)(Addrs.localPlayer + hazedumper::netvars::m_iHealth);
	std::cout << "[+] Health: " << std::dec << health << std::endl;
}

void FindAddr() {
	std::cout << "[*] Finding addresses..." << std::endl;
	// Get addresses
	GetModule();
	GetLocalPlayer();
}
// ================================================================================================================

void hackLoop() {
	// Get addresses and check health for debugging purposes
	FindAddr();

	// Main loop
	while (true) {

		// Exit key command 
		if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
			std::cout << "[*] Exiting..." << std::endl;
			break;
		}

		// Print health for debug
		if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			if (Addrs.localPlayer)
				HealthTest();
		}


		// Sleep(ms) for E F F I C E N C Y
		Sleep(10);
	}
}