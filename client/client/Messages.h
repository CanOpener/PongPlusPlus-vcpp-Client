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

