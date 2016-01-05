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
	BYTE bts[24];
	uint32_t x1 = 7483;
	string x2 = "Cool";
	uint8_t x3 = 75;
	string x4 = "Hey!";
	string x5 = "Hello!";
	uint16_t x6 = 324;

	auto seeker = bts;
	binaryConverter::writeUint32(&seeker, x1);
	binaryConverter::writeString(&seeker, x2);
	binaryConverter::writeUint8 (&seeker, x3);
	binaryConverter::writeString(&seeker, x4);
	binaryConverter::writeString(&seeker, x5);
	binaryConverter::writeUint16(&seeker, x6);
	seeker = bts;

	cout << "32uint : " << (int)binaryConverter::readUint32(&seeker) << endl;
	cout << "string : " << binaryConverter::readString(&seeker) << endl;
	cout << "8uint : " << (int)binaryConverter::readUint8(&seeker) << endl;
	cout << "string : " << binaryConverter::readString(&seeker) << endl;
	cout << "string : " << binaryConverter::readString(&seeker) << endl;
	cout << "16uint : " << (int)binaryConverter::readUint16(&seeker) << endl << endl;
	return 0;
}

