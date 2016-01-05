#include "stdafx.h"
#include <cstdint>
#include <SDL_net.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "binaryConverter.h"
using namespace std;

typedef unsigned char BYTE;

struct message {
	BYTE* data;
	int dataSize;
	message() { data = NULL; dataSize = 0; };
	message(BYTE* d, int ds) { data = d; dataSize = ds; }
};

class requestAliasMsg {
private:
	uint8_t mType;
	string alias;

public:
	requestAliasMsg(string);
	message bytes();
};

requestAliasMsg::requestAliasMsg(string al) {
	mType = 1;
	alias = al;
}

message requestAliasMsg::bytes() {
	message retMsg;
	retMsg.dataSize = alias.length() + 2; // +1 for mtype and +1 for null termination
	auto strBts = alias.c_str();
	retMsg.data = new BYTE[retMsg.dataSize];
	retMsg.data[0] = mType;
	memcpy(retMsg.data+1, strBts, alias.length());
	retMsg.data[retMsg.dataSize - 1] = 0; // null terminator
	return retMsg;
}

message prefixMessage(message m) {
	auto newlen = 2 + m.dataSize;
	auto retBts = new BYTE[newlen];
	auto size16 = (uint16_t)m.dataSize;
	memcpy(retBts, &size16, 2);
	memcpy(retBts + 2, m.data, m.dataSize);
	return message(retBts, newlen);
}

int main(int argc, char *argv[])
{
	BYTE bts[14];
	uint32_t x1 = 7483;
	uint8_t x2 = 32;
	auto x3 = "Hello!\0";
	uint16_t x4 = 324;
	auto seeker = bts;
	
	memcpy(seeker, &x1, 4);
	seeker += 4;
	memcpy(seeker, &x2, 1);
	seeker += 1;
	memcpy(seeker, x3, 7);
	seeker += 7;
	memcpy(seeker, &x4, 2);
	seeker += 2;

	seeker = bts;

	cout << "32uint : " << (int)binaryConverter::getUint32(&seeker) << endl;
	cout << "8uint : " << (int)binaryConverter::getUint8(&seeker) << endl;
	cout << "string : " << binaryConverter::getString(&seeker) << endl;
	cout << "16uint : " << (int)binaryConverter::getUint16(&seeker) << endl << endl;
	
	cout << "sizeof uint8_t : " << sizeof(uint8_t) << endl;
	cout << "sizeof uint16_t : " << sizeof(uint16_t) << endl;
	cout << "sizeof uint32_t : " << sizeof(uint32_t) << endl;
	cout << "sizeof int : " << sizeof(int) << endl;
	cout << "sizeof long : " << sizeof(long) << endl;
	cout << "sizeof long long : " << sizeof(long long) << endl;
	return 0;
}

