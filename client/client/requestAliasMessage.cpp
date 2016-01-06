#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <string>
#include <cstdint>

requestAliasMessage::requestAliasMessage() : message(types::REQUEST_ALIAS) {}
requestAliasMessage::requestAliasMessage(string a) : message(types::REQUEST_ALIAS) {
	alias = a;
}
requestAliasMessage::requestAliasMessage(dataMessage* dm) {
	auto seeker = dm->getData();
	messageType = binaryConverter::readUint8(&seeker);
	alias		= binaryConverter::readString(&seeker);
	delete dm;
}

string requestAliasMessage::getAlias() {
	return alias;
}
void requestAliasMessage::setAlias(string a) {
	alias = a;
}

dataMessage* requestAliasMessage::getDataMessage() {
	auto len = alias.length() + 2; // 1 for message type 1 for null
	auto data = new BYTE[len];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeString(&seeker, alias);
	return new dataMessage(data, len);
}

