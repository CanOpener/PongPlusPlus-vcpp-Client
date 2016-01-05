#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"

createGameDeniedMessage::createGameDeniedMessage() : message(types::CREATE_GAME_DENIED) {}
createGameDeniedMessage::createGameDeniedMessage(string n, string r) : message(types::CREATE_GAME_DENIED) {
	gameName = n;
	reason = r;
}
createGameDeniedMessage::createGameDeniedMessage(dataMessage* dm) {
	auto seeker = dm->getData();
	messageType = binaryConverter::readUint8(&seeker);
	gameName	= binaryConverter::readString(&seeker);
	reason		= binaryConverter::readString(&seeker);
	delete dm;
}

string createGameDeniedMessage::getGameName() {
	return gameName;
}
void createGameDeniedMessage::setGameName(string n) {
	gameName = n;
}

string createGameDeniedMessage::getReason() {
	return reason;
}
void createGameDeniedMessage::setReason(string r) {
	reason = r;
}

dataMessage* createGameDeniedMessage::getDataMessage() {
	auto len = gameName.length() + reason.length() + 3; // 1 for message type 1 for null
	auto data = new BYTE[len];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeString(&seeker, gameName);
	binaryConverter::writeString(&seeker, reason);
	return new dataMessage(data, len);
}