#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <cstdint>

gameOverMessage::gameOverMessage() : message(types::GAME_OVER) {};
gameOverMessage::gameOverMessage(uint8_t ys, uint8_t os, uint8_t st) : message(types::GAME_OVER) {
	yourScore	= ys;
	othersScore = os;
	status		= st;
}
gameOverMessage::gameOverMessage(dataMessage* dm) {
	auto seeker = dm->getData();
	messageType = binaryConverter::readUint8(&seeker);
	yourScore	= binaryConverter::readUint8(&seeker);
	othersScore = binaryConverter::readUint8(&seeker);
	status		= binaryConverter::readUint8(&seeker);
	delete dm;
}

uint8_t gameOverMessage::getYourScore() {
	return yourScore;
}
void gameOverMessage::setYourScore(uint8_t ys) {
	yourScore = ys;
}

uint8_t gameOverMessage::getOthersScore() {
	return othersScore;
}
void gameOverMessage::setOtherScore(uint8_t os) {
	othersScore = os;
}

uint8_t gameOverMessage::getStatus() {
	return status;
}
void gameOverMessage::setStatus(uint8_t st) {
	status = st;
}

dataMessage* gameOverMessage::getDataMessage() {
	auto len = 4;
	auto data = new BYTE[len];
	auto seeker = data;

	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeUint8(&seeker, yourScore);
	binaryConverter::writeUint8(&seeker, othersScore);
	binaryConverter::writeUint8(&seeker, status);

	return new dataMessage(data, len);
}