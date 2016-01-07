#include "stdafx.h"
#include "Messages.h"
#include "binaryConverter.h"
#include <cstdint>

stateUpdateMessage::stateUpdateMessage() : message(types::STATE_UPDATE) {};
stateUpdateMessage::stateUpdateMessage(uint8_t cr, uint8_t p1s, uint8_t p2s,
	uint16_t p1p, uint16_t p2p, uint16_t bx, uint16_t by) : message(types::STATE_UPDATE) {
	
	currentRound = cr;
	p1Score		 = p1s;
	p2Score		 = p2s;
	p1Pos		 = p1p;
	p2Pos		 = p2p;
	ballX		 = bx;
	ballY		 = by;
}
stateUpdateMessage::stateUpdateMessage(dataMessage dm) {
	auto seeker  = dm.getData();
	messageType  = binaryConverter::readUint8(&seeker);
	currentRound = binaryConverter::readUint8(&seeker);
	p1Score		 = binaryConverter::readUint8(&seeker);
	p2Score		 = binaryConverter::readUint8(&seeker);
	p1Pos		 = binaryConverter::readUint16(&seeker);
	p2Pos		 = binaryConverter::readUint16(&seeker);
	ballX		 = binaryConverter::readUint16(&seeker);
	ballY		 = binaryConverter::readUint16(&seeker);
}

uint8_t stateUpdateMessage::getCurrentRound() {
	return currentRound;
}
void stateUpdateMessage::setCurrentRound(uint8_t cr) {
	currentRound = cr;
}

uint8_t stateUpdateMessage::getPlayer1Score() {
	return p1Score;
}
void stateUpdateMessage::setPlayer1Score(uint8_t p1s) {
	p1Score = p1s;
}

uint8_t stateUpdateMessage::getPlayer2Score() {
	return p2Score;
}
void stateUpdateMessage::setPlayer2Score(uint8_t p2s) {
	p2Score = p2s;
}

uint16_t stateUpdateMessage::getPlayer1Position() {
	return p1Pos;
}
void stateUpdateMessage::setPlayer1Position(uint16_t p1p) {
	p1Pos = p1p;
}

uint16_t stateUpdateMessage::getPlayer2Position() {
	return p2Pos;
}
void stateUpdateMessage::setPlayer2Position(uint16_t p2p) {
	p2Pos = p2p;
}

uint16_t stateUpdateMessage::getBallX() {
	return ballX;
}
void stateUpdateMessage::setBallX(uint16_t bx) {
	ballX = bx;
}

uint16_t stateUpdateMessage::getBallY() {
	return ballY;
}
void stateUpdateMessage::setBallY(uint16_t by) {
	ballY = by;
}

dataMessage* stateUpdateMessage::getDataMessage() {
	auto len	= 12;
	auto data	= new BYTE[len];
	auto seeker = data;

	binaryConverter::writeUint8(&seeker, messageType);
	binaryConverter::writeUint8(&seeker, currentRound);
	binaryConverter::writeUint8(&seeker, p1Score);
	binaryConverter::writeUint8(&seeker, p2Score);
	binaryConverter::writeUint16(&seeker, p1Pos);
	binaryConverter::writeUint16(&seeker, p2Pos);
	binaryConverter::writeUint16(&seeker, ballX);
	binaryConverter::writeUint16(&seeker, ballY);

	return new dataMessage(data, len);
}