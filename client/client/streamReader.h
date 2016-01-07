#pragma once
#include "SDL_net.h"

class streamReader
{
	static message* getMessage(dataMessage dm);
public:

	static void startReader(TCPsocket sock);

};

