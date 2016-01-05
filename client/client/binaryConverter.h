#pragma once
#include "stdafx.h"
#include <cstdint>
#include <string>
using namespace std;

class binaryConverter
{
public:
	static uint8_t getUint8(BYTE** seeker);
	static uint16_t getUint16(BYTE** seeker);
	static uint32_t getUint32(BYTE** seeker);
	static string getString(BYTE** seeker);
};

