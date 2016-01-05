#include "stdafx.h"
#include <cstdint>
#include <SDL_net.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "binaryConverter.h"
#include "Messages.h"
using namespace std;

int main(int argc, char *argv[])
{
	requestAliasMessage request("This username should be waaaaayyy too long");
	auto dm = request.getDataMessage();
	dm->prefix();

	SDLNet_Init();

	IPaddress ip;
	SDLNet_ResolveHost(&ip, "pong.dynastysoftware.net", 3000);

	BYTE recv[100];
	TCPsocket socket = SDLNet_TCP_Open(&ip);
	SDLNet_TCP_Send(socket, dm->getData(), dm->getDataLength());
	SDLNet_TCP_Recv(socket, recv, 100);

	auto seeker = recv;
	auto size = binaryConverter::readUint16(&seeker);
	auto messg = new BYTE[size];
	memcpy(messg, seeker, size);
	auto newDm = new dataMessage(messg, size);
	auto mType = binaryConverter::readUint8(&seeker);

	if (mType == types::ALIAS_APPROVED) {
		auto accepted = aliasApprovedMessage(newDm);
		cout << "Accepted!!" << endl;
	}
	else if (mType == types::ALIAS_DENIED) {
		auto denied = aliasDeniedMessage(newDm);
		cout << "Denied : " << denied.getReason() << endl;
	}
	else {
		cout << "Unknown message received" << endl;
	}

	return 0;
}

