#pragma once
#include "stdafx.h"
#include "gameDescriptor.h"
#include <vector>
#include <cstdint>
#include <string>
using namespace std;

class dataMessage {
private:
	bool destroyed;
	bool prefixed;
	int dataLength;
	BYTE* data;

public:
	dataMessage(BYTE* d, int size);
	~dataMessage();

	bool isDestroyed();
	bool isPrefixed();
	int getDataLength();
	BYTE* getData();

	void scrubData();
	void prefix();
};

enum types : uint8_t {
	REQUEST_ALIAS = 1,
	ALIAS_APPROVED,
	ALIAS_DENIED,
	REQUEST_GAME_LIST,
	GAME_LIST,
	CREATE_GAME,
	CREATE_GAME_APPROVED,
	CREATE_GAME_DENIED,
	JOIN_GAME,
	JOIN_GAME_DENIED,
	LEAVE_GAME,
	START_GAME,
	STATE_UPDATE,
	GAME_OVER,
	MOVE
};

class message
{
protected:
	uint8_t messageType;
public:
	message();
	message(uint8_t typ);

	virtual uint8_t getMessageType();
	virtual void setMessageType(uint8_t typ);

	virtual dataMessage* getDataMessage() = 0;
};

class requestAliasMessage : public message
{
private:
	string alias;
public:
	requestAliasMessage();
	requestAliasMessage(string a);
	requestAliasMessage(dataMessage* dm);

	string getAlias();
	void setAlias(string a);

	dataMessage* getDataMessage();
};

class aliasApprovedMessage : public message
{
public:
	aliasApprovedMessage();
	aliasApprovedMessage(dataMessage* dm);

	dataMessage* getDataMessage();
};

class aliasDeniedMessage : public message
{
	string reason;
public:
	aliasDeniedMessage();
	aliasDeniedMessage(string r);
	aliasDeniedMessage(dataMessage* dm);

	string getReason();
	void setReason(string r);

	dataMessage* getDataMessage();
};

class requestGameListMessage : public message
{
public:
	requestGameListMessage();
	requestGameListMessage(dataMessage* dm);

	dataMessage* getDataMessage();
};

class gameListMessage : public message
{
private:
	vector<gameDescriptor> games;

public:
	gameListMessage();
	gameListMessage(vector<gameDescriptor> vgd);
	gameListMessage(dataMessage* dm);

	vector<gameDescriptor> getGames();
	void setGames(vector<gameDescriptor> vgd);

	dataMessage* getDataMessage();
};

class createGameMessage : public message
{
private:
	string gameName;
public:
	createGameMessage();
	createGameMessage(string n);
	createGameMessage(dataMessage* dm);

	string getGameName();
	void setGameName(string n);

	dataMessage* getDataMessage();
};

class createGameApprovedMessage : public message 
{
private:
	string gameID;
	string gameName;

public:
	createGameApprovedMessage();
	createGameApprovedMessage(string id, string n);
	createGameApprovedMessage(dataMessage* dm);

	string getGameID();
	void setGameID(string id);

	string getGameName();
	void setGameName(string n);

	dataMessage* getDataMessage();
};

class createGameDeniedMessage : public message
{
private:
	string gameName;
	string reason;
public:
	createGameDeniedMessage();
	createGameDeniedMessage(string n, string r);
	createGameDeniedMessage(dataMessage* dm);

	string getGameName();
	void setGameName(string n);

	string getReason();
	void setReason(string r);

	dataMessage* getDataMessage();
};

class joinGameMessage : public message
{
private:
	string gameID;

public:
	joinGameMessage();
	joinGameMessage(string gid);
	joinGameMessage(dataMessage* dm);

	string getGameID();
	void setGameID(string gid);

	dataMessage* getDataMessage();
};

class joinGameDeniedMessage : public message
{
private:
	string reason;

public:
	joinGameDeniedMessage();
	joinGameDeniedMessage(string r);
	joinGameDeniedMessage(dataMessage* dm);

	string getReason();
	void setReason(string r);

	dataMessage* getDataMessage();
};


class leaveGameMessage : public message
{
public:
	leaveGameMessage();
	leaveGameMessage(dataMessage* dm);

	dataMessage* getDataMessage();
};

class startGameMessage : public message
{
private:
	bool left;
	uint16_t yPos;
	uint16_t othersPos;
	uint16_t ballX;
	uint16_t ballY;
	string othersAlias;
	string gameID;
	string gameName;

public:
	startGameMessage();
	startGameMessage(bool l, uint16_t ypo, uint16_t opo, uint16_t bx, uint16_t by, string oa, string gid, string gn);
	startGameMessage(dataMessage* dm);

	bool getLeft();
	void setLeft(bool l);

	uint16_t getYourPosition();
	void setYourPosition(uint16_t yp);

	uint16_t getOthersPosition();
	void setOthersPosition(uint16_t op);

	uint16_t getBallX();
	void setBallX(uint16_t bx);

	uint16_t getBallY();
	void setBallY(uint16_t by);
	
	string getOthersAlias();
	void setOthersAlias(string oa);

	string getGameID();
	void setGameID(string gid);

	string getGameName();
	void setGameName(string gn);

	dataMessage* getDataMessage();
};

class stateUpdateMessage : public message {
private:
	uint8_t currentRound;
	uint8_t p1Score;
	uint8_t p2Score;
	uint16_t p1Pos;
	uint16_t p2Pos;
	uint16_t ballX;
	uint16_t ballY;

public:
	stateUpdateMessage();
	stateUpdateMessage(uint8_t cr, uint8_t p1s, uint8_t p2s, uint16_t p1p, uint16_t p2p, uint16_t bx, uint16_t by);
	stateUpdateMessage(dataMessage* dm);

	uint8_t getCurrentRound();
	void setCurrentRound(uint8_t cr);

	uint8_t getPlayer1Score();
	void setPlayer1Score(uint8_t p1s);

	uint8_t getPlayer2Score();
	void setPlayer2Score(uint8_t p2s);
	
	uint16_t getPlayer1Position();
	void setPlayer1Position(uint16_t p1p);

	uint16_t getPlayer2Position();
	void setPlayer2Position(uint16_t p2p);
	
	uint16_t getBallX();
	void setBallX(uint16_t bx);

	uint16_t getBallY();
	void setBallY(uint16_t by);

	dataMessage* getDataMessage();
};

class gameOverMessage : public message
{
private:
	uint8_t yourScore;
	uint8_t othersScore;
	uint8_t status;

public:
	gameOverMessage();
	gameOverMessage(uint8_t ys, uint8_t os, uint8_t st);
	gameOverMessage(dataMessage* dm);
	
	uint8_t getYourScore();
	void setYourScore(uint8_t ys);

	uint8_t getOthersScore();
	void setOtherScore(uint8_t os);

	uint8_t getStatus();
	void setStatus(uint8_t st);
	
	dataMessage* getDataMessage();
};

class moveMessage : public message
{
private:
	uint16_t position;

public:
	moveMessage();
	moveMessage(uint16_t p);
	moveMessage(dataMessage* dm);

	uint16_t getPosition();
	void setPosition(uint16_t ps);

	dataMessage* getDataMessage();
};