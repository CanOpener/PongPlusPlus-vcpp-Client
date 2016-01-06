#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <cstdint>

leaveGameMessage::leaveGameMessage() : message(types::LEAVE_GAME) {}
leaveGameMessage::leaveGameMessage(dataMessage* dm) {
	auto seeker = dm->getData();
	messageType = binaryConverter::readUint8(&seeker);
	delete dm;
}

dataMessage* leaveGameMessage::getDataMessage() {
	auto data = new BYTE[1];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	return new dataMessage(data, 1);
}

