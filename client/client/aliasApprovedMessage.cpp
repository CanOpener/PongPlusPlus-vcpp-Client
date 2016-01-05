#include "stdafx.h"
#include "aliasApprovedMessage.h"
#include "binaryConverter.h"

aliasApprovedMessage::aliasApprovedMessage() : message(types::ALIAS_APPROVED) {}
aliasApprovedMessage::aliasApprovedMessage(dataMessage* dm) {
	auto seeker = dm->getData();
	messageType = binaryConverter::readUint8(&seeker);
	delete dm;
}

dataMessage* aliasApprovedMessage::getDataMessage() {
	auto data = new BYTE[1];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	return new dataMessage(data, 1);
}

