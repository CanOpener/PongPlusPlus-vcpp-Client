#pragma once
#include "stdafx.h"
#include "SDL_net.h"

class streamReader
{
private:
	static message* getMessage(dataMessage dm);

public:
	static void startReader(TCPsocket sock);
};

