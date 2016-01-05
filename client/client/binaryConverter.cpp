#include "stdafx.h"
#include "binaryConverter.h"
#include <cstdint>
#include <string>

uint8_t binaryConverter::getUint8(BYTE** seeker) {
	uint8_t retInt = **(seeker);
	*seeker++;
	return retInt;
}
uint16_t binaryConverter::getUint16(BYTE** seeker) {
	uint16_t* p = (uint16_t*)*seeker;
	uint16_t retInt = *p;
	*seeker+=sizeof(uint16_t);
	return retInt;
}
uint32_t binaryConverter::getUint32(BYTE** seeker) {
	uint32_t* p = (uint32_t*)(*seeker);
	uint32_t retInt = *p;
	*seeker += sizeof(uint32_t);
	return retInt;
}
string binaryConverter::getString(BYTE** seeker) {
	string str((const char*)(*seeker));
	*seeker += str.length() + 1; // skip null
	return str;
}
