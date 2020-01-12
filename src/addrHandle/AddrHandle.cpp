#include <iostream>
#include <Windows.h>
#include "AddrHandle.h"
#include "../haze/haze.hpp"

struct GameAddresses {
	uintptr_t module;
	uintptr_t localPlayer;
}Addrs;

void GetModule() {
	Addrs.module = (uintptr_t)GetModuleHandle("client_panorama.dll");
	std::cout << "[+] Found Module Address (client_panorama.dll) -> 0x" << std::hex << Addrs.module << std::endl;
}

void GetLocalPlayer() {
	if (Addrs.localPlayer == NULL) {
		do {
			Addrs.localPlayer = *(uintptr_t*)(Addrs.module + hazedumper::signatures::dwLocalPlayer);
		} while (Addrs.localPlayer == NULL);
	}
	std::cout << "[+] Found LocalPlayer PTR -> 0x" << std::hex << Addrs.localPlayer << std::endl;
}

void HealthTest() {
	std::cout << "\nHEALTH TEST\n//////////////////\n" << std::endl;
	int health = *(uintptr_t*)(Addrs.localPlayer + hazedumper::netvars::m_iHealth);
	std::cout << "[+] Health: 0x" << health << "\n" << std::endl;
}