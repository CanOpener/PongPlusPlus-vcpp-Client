#pragma once
#pragma once
#include "stdafx.h"
#include "Messages.h"
#include <deque>
#include <mutex>
using namespace std;

class messageQueue
{
private:
	mutex mu;
	deque<message*> que;

public:
	static messageQueue& instance();

	void addMessage(message* ms);
	deque<message*> getQue();
};

