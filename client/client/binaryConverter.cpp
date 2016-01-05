#include "stdafx.h"
#include "binaryConverter.h"
#include <cstdint>
#include <string>

uint8_t binaryConverter::readUint8(BYTE** seeker) {
	uint8_t retInt = **(seeker);
	(*seeker)++;
	return retInt;
}
uint16_t binaryConverter::readUint16(BYTE** seeker) {
	uint16_t* p = (uint16_t*)*seeker;
	uint16_t retInt = *p;
	(*seeker) += sizeof(uint16_t);
	return retInt;
}
uint32_t binaryConverter::readUint32(BYTE** seeker) {
	uint32_t* p = (uint32_t*)(*seeker);
	uint32_t retInt = *p;
	(*seeker) += sizeof(uint32_t);
	return retInt;
}
string binaryConverter::readString(BYTE** seeker) {
	string str((const char*)(*seeker));
	(*seeker) += str.length() + 1; // skip null
	return str;
}

void binaryConverter::writeUint8(BYTE** seeker, uint8_t data) {
	**seeker = data;
	(*seeker)++;
}
void binaryConverter::writeUint16(BYTE** seeker, uint16_t data) {
	memcpy(*seeker, &data, sizeof(uint16_t));
	(*seeker) += sizeof(uint16_t);
}
void binaryConverter::writeUint32(BYTE** seeker, uint32_t data) {
	memcpy(*seeker, &data, sizeof(uint32_t));
	(*seeker) += sizeof(uint32_t);
}
void binaryConverter::writeString(BYTE** seeker, string data) {
	auto len = data.length();
	auto cStr = data.c_str();
	memcpy(*seeker, cStr, len);
	(*seeker) += len;
	**seeker = 0; // null terminator
	(*seeker)++;
}
