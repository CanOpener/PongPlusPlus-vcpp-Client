#pragma once
#pragma once
#include "stdafx.h"
#include "SDL_net.h"
#include "Messages.h"
#include <deque>
#include <mutex>
using namespace std;

class messageQueue
{
private:
	static mutex mu;
	static deque<message*> que;

public:
	static void addMessage(message* ms);
	static deque<message*> getQue();
};

