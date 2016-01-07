#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <string>
#include <cstdint>

createGameApprovedMessage::createGameApprovedMessage() : message(types::CREATE_GAME_APPROVED) {}
createGameApprovedMessage::createGameApprovedMessage(string id, string n) : message(types::CREATE_GAME_APPROVED) {
	gameID = id;
	gameName = n;
}
createGameApprovedMessage::createGameApprovedMessage(dataMessage dm) {
	auto seeker = dm.getData();
	messageType = binaryConverter::readUint8(&seeker);
	gameID		= binaryConverter::readString(&seeker);
	gameName	= binaryConverter::readString(&seeker);
}

string createGameApprovedMessage::getGameID() {
	return gameID;
}
void createGameApprovedMessage::setGameID(string id) {
	gameID = id;
}

string createGameApprovedMessage::getGameName() {
	return gameName;
}
void createGameApprovedMessage::setGameName(string n) {
	gameName = n;
}

dataMessage* createGameApprovedMessage::getDataMessage() {
	auto len = 1 + gameID.length() + gameName.length() + 2;
	auto data = new BYTE[len];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeString(&seeker, gameID);
	binaryConverter::writeString(&seeker, gameName);
	return new dataMessage(data, len);
}