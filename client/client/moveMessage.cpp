#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <string>
#include <cstdint>

moveMessage::moveMessage() : message(types::MOVE) {}
moveMessage::moveMessage(uint16_t p) : message(types::MOVE) {
	position = p;
}
moveMessage::moveMessage(dataMessage dm) {
	auto seeker = dm.getData();
	messageType = binaryConverter::readUint8(&seeker);
	position = binaryConverter::readUint16(&seeker);
}

uint16_t moveMessage::getPosition() {
	return position;
}
void moveMessage::setPosition(uint16_t ps) {
	position = ps;
}

dataMessage* moveMessage::getDataMessage() {
	auto len = 3;
	auto data = new BYTE[len];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeUint16(&seeker, position);
	return new dataMessage(data, len);
}