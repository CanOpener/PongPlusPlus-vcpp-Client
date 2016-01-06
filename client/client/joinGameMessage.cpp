#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <string>
#include <cstdint>


joinGameMessage::joinGameMessage() : message(types::JOIN_GAME) {};
joinGameMessage::joinGameMessage(string gid) : message(types::JOIN_GAME) {
	gameID = gid;
}
joinGameMessage::joinGameMessage(dataMessage* dm) {
	auto seeker = dm->getData();
	messageType = binaryConverter::readUint8(&seeker);
	gameID = binaryConverter::readString(&seeker);
	delete dm;
}

string joinGameMessage::getGameID() {
	return gameID;
}
void joinGameMessage::setGameID(string gid) {
	gameID = gid;
}

dataMessage* joinGameMessage::getDataMessage() {
	auto len = 2 + gameID.length();
	auto data = new BYTE[len];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeString(&seeker, gameID);
	return new dataMessage(data, len);
}