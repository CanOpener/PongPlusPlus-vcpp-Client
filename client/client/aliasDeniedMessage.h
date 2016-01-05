#pragma once
#include "Messages.h"
#include <string>
using namespace std;

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

