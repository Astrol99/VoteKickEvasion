#include <iostream>
#include <Windows.h>
#include "Evade.h"
#include "../addrHandle/AddrHandle.h"

void hackLoop() {
	// Get addresses
	GetModule();
	GetLocalPlayer();
	HealthTest();
}