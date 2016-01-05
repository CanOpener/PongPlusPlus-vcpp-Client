#pragma once
#include "stdafx.h"
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