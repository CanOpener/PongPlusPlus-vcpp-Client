#include "stdafx.h"
#include "SDL_net.h"
#include "Messages.h"
#include "messageQueue.h"
#include <deque>
#include <mutex>


void messageQueue::addMessage(message* ms) {
	lock_guard<mutex> locker(mu);
	que.push_back(ms);
}
deque<message*> messageQueue::getQue() {
	lock_guard<mutex> locker(mu);
	deque<message*> retQue = que;
	que.clear();
	return retQue;
}
