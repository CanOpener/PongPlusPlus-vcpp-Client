#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <string>
#include <cstdint>

aliasDeniedMessage::aliasDeniedMessage() : message(types::ALIAS_DENIED) {}
aliasDeniedMessage::aliasDeniedMessage(string r) : message(types::ALIAS_DENIED) {
	reason = r;
}
aliasDeniedMessage::aliasDeniedMessage(dataMessage* dm) {
	auto seeker = dm->getData();
	messageType = binaryConverter::readUint8(&seeker);
	reason		= binaryConverter::readString(&seeker);
	delete dm;
}

string aliasDeniedMessage::getReason() {
	return reason;
}
void aliasDeniedMessage::setReason(string r) {
	reason = r;
}

dataMessage* aliasDeniedMessage::getDataMessage() {
	auto len = reason.length() + 2; // 1 for message type 1 for null
	auto data = new BYTE[len];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeString(&seeker, reason);
	return new dataMessage(data, len);
}