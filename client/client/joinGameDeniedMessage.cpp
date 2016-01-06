#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <string>
#include <cstdint>

joinGameDeniedMessage::joinGameDeniedMessage() : message(types::JOIN_GAME_DENIED) {}
joinGameDeniedMessage::joinGameDeniedMessage(string r) : message(types::JOIN_GAME_DENIED) {
	reason = r;
}
joinGameDeniedMessage::joinGameDeniedMessage(dataMessage* dm) {
	auto seeker = dm->getData();
	messageType = binaryConverter::readUint8(&seeker);
	reason = binaryConverter::readString(&seeker);
	delete dm;
}

string joinGameDeniedMessage::getReason() {
	return reason;
}
void joinGameDeniedMessage::setReason(string r) {
	reason = r;
}

dataMessage* joinGameDeniedMessage::getDataMessage() {
	auto len = reason.length() + 2; // 1 for message type 1 for null
	auto data = new BYTE[len];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeString(&seeker, reason);
	return new dataMessage(data, len);
}