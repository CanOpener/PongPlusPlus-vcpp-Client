#pragma once
#include "Messages.h"

class aliasApprovedMessage : public message
{
public:
	aliasApprovedMessage();
	aliasApprovedMessage(dataMessage* dm);

	dataMessage* getDataMessage();
};

