#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <cstdint>

// dataMessage
dataMessage::dataMessage(BYTE* d, int size) {
	data = d;
	dataLength = size;
	prefixed = false;
	destroyed = false;
}
dataMessage::~dataMessage() {
	scrubData();
}

bool dataMessage::isDestroyed() {
	return destroyed;
}

bool dataMessage::isPrefixed() {
	return prefixed;
}
int dataMessage::getDataLength() {
	return dataLength;
}
BYTE* dataMessage::getData() {
	return data;
}

void dataMessage::scrubData() {
	delete[] data;
	destroyed = true;
}

void dataMessage::prefix() {
	auto newData = new BYTE[dataLength + 2]; // 16 bit prefix
	auto len16 = (uint16_t)dataLength;
	auto seeker = newData;
	binaryConverter::writeUint16(&seeker, len16);
	memcpy(seeker, data, dataLength);
	delete[] data;
	data = newData;
	dataLength += 2;
	prefixed = true;
}


// message
message::message() {
	messageType = 0;
}

message::message(uint8_t typ) {
	messageType = typ;
}

uint8_t message::getMessageType() {
	return messageType;
}

void message::setMessageType(uint8_t typ) {
	messageType = typ;
}