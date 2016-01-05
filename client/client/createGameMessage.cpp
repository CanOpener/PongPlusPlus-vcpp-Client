#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"

createGameMessage::createGameMessage() : message(types::CREATE_GAME) {}
createGameMessage::createGameMessage(string n) : message(types::CREATE_GAME) {
	gameName = n;
}
createGameMessage::createGameMessage(dataMessage* dm) {
	auto seeker = dm->getData();
	messageType = binaryConverter::readUint8(&seeker);
	gameName	= binaryConverter::readString(&seeker);
	delete dm;
}

string createGameMessage::getGameName() {
	return gameName;
}
void createGameMessage::setGameName(string n) {
	gameName = n;
}

dataMessage* createGameMessage::getDataMessage() {
	auto len = gameName.length() + 2; // 1 for message type 1 for null
	auto data = new BYTE[len];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeString(&seeker, gameName);
	return new dataMessage(data, len);
}

