#include "messageQueue.h"


messageQueue& messageQueue::instance() {
	static messageQueue mq;
	return mq;
}
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
