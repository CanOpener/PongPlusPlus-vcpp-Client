#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <cstdint>

// dataMessage
dataMessage::dataMessage(BYTE* d, int size) {
	data = d;
	dataLength = size;
}
int dataMessage::getDataLength() {
	return dataLength;
}
BYTE* dataMessage::getData() {
	return data;
}

void dataMessage::scrubData() {
	delete[] data;
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