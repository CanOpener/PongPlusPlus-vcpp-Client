#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <cstdint>

aliasApprovedMessage::aliasApprovedMessage() : message(types::ALIAS_APPROVED) {}
aliasApprovedMessage::aliasApprovedMessage(dataMessage dm) {
	auto seeker = dm.getData();
	messageType = binaryConverter::readUint8(&seeker);
}

dataMessage* aliasApprovedMessage::getDataMessage() {
	auto data = new BYTE[1];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	return new dataMessage(data, 1);
}

