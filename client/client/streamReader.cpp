#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include "dataBuffer.h"
#include "streamReader.h"
#include "SDL_net.h"
#include <iostream>

message* streamReader::getMessage(dataMessage dm) {
	auto seeker = dm.getData();
	auto mType = binaryConverter::readUint8(&seeker);
	switch (mType) {
	case types::REQUEST_ALIAS:
		return new requestAliasMessage(dm);
	case types::ALIAS_APPROVED:
		return new aliasApprovedMessage(dm);
	case types::ALIAS_DENIED:
		return new aliasDeniedMessage(dm);
	case types::REQUEST_GAME_LIST:
		return new requestGameListMessage(dm);
	case types::GAME_LIST:
		return new gameListMessage(dm);
	case types::CREATE_GAME:
		return new createGameMessage(dm);
	case types::CREATE_GAME_APPROVED:
		return new createGameApprovedMessage(dm);
	case types::CREATE_GAME_DENIED:
		return new createGameDeniedMessage(dm);
	case types::JOIN_GAME:
		return new joinGameMessage(dm);
	case types::JOIN_GAME_DENIED:
		return new joinGameDeniedMessage(dm);
	case types::LEAVE_GAME:
		return new leaveGameMessage(dm);
	case types::START_GAME:
		return new startGameMessage(dm);
	case types::STATE_UPDATE:
		return new stateUpdateMessage(dm);
	case types::GAME_OVER:
		return new gameOverMessage(dm);
	case types::MOVE:
		return new moveMessage(dm);
	default :
		return NULL;
	}

}

void streamReader::startReader(TCPsocket sock) {
	dataBuffer buf(1024);
	int bytesToRead = 0;

	while (true) {
		BYTE data[1024];
		auto size = SDLNet_TCP_Recv(sock, data, 2014);
		if (size <= 0) {
			// connection closed
			std::cout << "Connection closed, reader stopping\n";
			return;
		}
		buf.write(data, size);

		while (buf.getSize() > 1) {
			if (bytesToRead == 0) {
				int read;
				auto prefix = buf.read(2, read);
				auto seeker = prefix;
				bytesToRead = (int)binaryConverter::readUint16(&seeker);
				delete[] prefix;
			}
			if (buf.getSize() >= bytesToRead) {
				int read;
				auto message = buf.read(bytesToRead, read);
				dataMessage dm(message, read);
				auto messageToSend = streamReader::getMessage(dm);
				if (messageToSend != NULL) {
					// send messageToSend somewhere
				}
				dm.scrubData();
				delete[] message;
				bytesToRead = 0;
			} else {
				break;
			}
		}
	}
}