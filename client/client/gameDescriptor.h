#pragma once
#include "stdafx.h"
#include <cstdint>
#include <string>
using namespace std;

struct gameDescriptor {
	uint32_t initTime;
	string gID;
	string gName;
	string initiator;

	int getSize() {
		return 4 + gID.length() + gName.length() + initiator.length() + 3;
	}
};