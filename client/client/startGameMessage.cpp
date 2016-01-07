#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <string>
#include <cstdint>

startGameMessage::startGameMessage() : message(types::START_GAME) {}
startGameMessage::startGameMessage(bool l, uint16_t ypo, uint16_t opo,
	uint16_t bx, uint16_t by, string oa, string gid, string gn) : message(types::START_GAME) {
	left		= l;
	yPos		= ypo;
	othersPos	= opo;
	ballX		= bx;
	ballY		= by;
	othersAlias = oa;
	gameID		= gid;
	gameName	= gameName;
}
startGameMessage::startGameMessage(dataMessage dm) {
	auto seeker = dm.getData();
	messageType = binaryConverter::readUint8(&seeker);
	left		= (binaryConverter::readUint8(&seeker) != 0);
	yPos		= binaryConverter::readUint16(&seeker);
	othersPos	= binaryConverter::readUint16(&seeker);
	ballX		= binaryConverter::readUint16(&seeker);
	ballY		= binaryConverter::readUint16(&seeker);
	othersAlias = binaryConverter::readString(&seeker);
	gameID		= binaryConverter::readString(&seeker);
	gameName	= binaryConverter::readString(&seeker);
}

bool startGameMessage::getLeft() {
	return left;
}
void startGameMessage::setLeft(bool l) {
	left = l;
}

uint16_t startGameMessage::getYourPosition() {
	return yPos;
}
void startGameMessage::setYourPosition(uint16_t yp) {
	yPos = yp;
}

uint16_t startGameMessage::getOthersPosition() {
	return othersPos;
}
void startGameMessage::setOthersPosition(uint16_t op) {
	othersPos = op;
}

uint16_t startGameMessage::getBallX() {
	return ballX;
}
void startGameMessage::setBallX(uint16_t bx) {
	ballX = bx;
}

uint16_t startGameMessage::getBallY() {
	return ballY;
}
void startGameMessage::setBallY(uint16_t by) {
	ballY = by;
}

string startGameMessage::getOthersAlias() {
	return othersAlias;
}
void startGameMessage::setOthersAlias(string oa) {
	othersAlias = oa;
}

string startGameMessage::getGameID() {
	return gameID;
}
void startGameMessage::setGameID(string gid) {
	gameID = gid;
}

string startGameMessage::getGameName() {
	return gameName;
}
void startGameMessage::setGameName(string gn) {
	gameName = gn;
}

dataMessage* startGameMessage::getDataMessage() {
	auto len = 13 + othersAlias.length() + gameID.length() + gameName.length();
	auto data = new BYTE[len];
	auto seeker = data;

	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeUint8(&seeker, (uint8_t)left);
	binaryConverter::writeUint16(&seeker, yPos);
	binaryConverter::writeUint16(&seeker, othersPos);
	binaryConverter::writeUint16(&seeker, ballX);
	binaryConverter::writeUint16(&seeker, ballY);
	binaryConverter::writeString(&seeker, othersAlias);
	binaryConverter::writeString(&seeker, gameID);
	binaryConverter::writeString(&seeker, gameName);

	return new dataMessage(data, len);
}