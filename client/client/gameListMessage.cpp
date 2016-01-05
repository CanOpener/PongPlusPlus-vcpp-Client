#include "stdafx.h"
#include "gameDescriptor.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <vector>
#include <cstdint>
#include <string>

using namespace std;

gameListMessage::gameListMessage() : message(types::GAME_LIST) {}
gameListMessage::gameListMessage(vector<gameDescriptor> vgd) : message(types::GAME_LIST) {
	games = vgd;
}
gameListMessage::gameListMessage(dataMessage* dm) {
	auto seeker   = dm->getData();
	messageType   = binaryConverter::readUint8(&seeker);
	auto numGames = binaryConverter::readUint16(&seeker);
	for (int i=0; i < numGames; i++) {
		gameDescriptor gd;
		gd.initTime  = binaryConverter::readUint32(&seeker);
		gd.gID		 = binaryConverter::readString(&seeker);
		gd.gName	 = binaryConverter::readString(&seeker);
		gd.initiator = binaryConverter::readString(&seeker);
		games.push_back(gd);
	}
	delete dm;
}

vector<gameDescriptor> gameListMessage::getGames() {
	return games;
}
void gameListMessage::setGames(vector<gameDescriptor> vgd) {
	games = vgd;
}

dataMessage* gameListMessage::getDataMessage() {
	uint16_t size = 3; // mtype and numGames
	for (auto g : games) {
		size += g.getSize();
	}

	auto data = new BYTE[size];
	auto seeker = data;
	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeUint16(&seeker, size);
	for (auto g : games) {
		binaryConverter::writeUint32(&seeker, g.initTime);
		binaryConverter::writeString(&seeker, g.gID);
		binaryConverter::writeString(&seeker, g.gName);
		binaryConverter::writeString(&seeker, g.initiator);
	}

	return new dataMessage(data, size);
}