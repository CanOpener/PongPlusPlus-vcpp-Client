#pragma once
#include "Messages.h"
#include <string>
using namespace std;

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

