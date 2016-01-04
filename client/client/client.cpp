#include "stdafx.h"
#include <cstdint>
#include <SDL_net.h>
#include <stdio.h>
#include <string>
#include <iostream>
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
	requestAliasMsg requestMsg("Windows");
	auto msg = prefixMessage(requestMsg.bytes());
	
	SDLNet_Init();

	IPaddress ip;
	SDLNet_ResolveHost(&ip, "pong.dynastysoftware.net", 3000);

	auto socket = SDLNet_TCP_Open(&ip);
	cout << "IP address: " << ip.host << endl;

	SDLNet_TCP_Send(socket, msg.data, msg.dataSize);

	SDLNet_TCP_Close(socket);
	SDLNet_Quit();
	return 0;
}

