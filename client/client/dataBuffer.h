#pragma once
#include "stdafx.h"

class dataBuffer
{
private:
	int front, back;
	int numBytes;
	int capacity;
	BYTE* data;

	void resize();
public:
	dataBuffer(int size);
	~dataBuffer();

	int getSize();
	int getCapacity();
	void write(BYTE* d, int size);
	BYTE* read(int size, int& actualSize);
	void print();
};



