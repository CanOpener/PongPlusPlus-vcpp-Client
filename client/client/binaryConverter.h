#pragma once
#include "stdafx.h"
#include <cstdint>
#include <string>
using namespace std;

class binaryConverter
{
public:
	static uint8_t readUint8(BYTE** seeker);
	static uint16_t readUint16(BYTE** seeker);
	static uint32_t readUint32(BYTE** seeker);
	static string readString(BYTE** seeker);

	static void writeUint8(BYTE** seeker, uint8_t data);
	static void writeUint16(BYTE** seeker, uint16_t data);
	static void writeUint32(BYTE** seeker, uint32_t data);
	static void writeString(BYTE** seeker, string data);
};

