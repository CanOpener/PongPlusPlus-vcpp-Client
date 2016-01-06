#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <cstdint>

requestGameListMessage::requestGameListMessage() : message(types::REQUEST_GAME_LIST) {}
requestGameListMessage::requestGameListMessage(dataMessage* dm) {
	auto seeker = dm->getData();
	messageType = binaryConverter::readUint8(&seeker);
	delete dm;
}

dataMessage* requestGameListMessage::getDataMessage() {
	auto data = new BYTE[1];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	return new dataMessage(data, 1);
}