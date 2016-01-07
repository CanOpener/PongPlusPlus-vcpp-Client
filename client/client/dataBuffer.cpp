#include "stdafx.h"
#include "dataBuffer.h"
#include <string.h>
#include <iostream>
using namespace std;

dataBuffer::dataBuffer(int size) {
	if (size < 0) {
		size = 0;
	}
	data = new BYTE[size];
	capacity = size;
	front = 0;
	back = 0;
	numBytes = 0;
}

dataBuffer::~dataBuffer() {
	if (capacity != 0) {
		delete[] data;
	}
}

void dataBuffer::resize() {
	auto newCapacity = capacity * 2;
	auto newData = new BYTE[newCapacity];
	if (numBytes + back <= capacity) {
		memcpy(newData, &data[back], numBytes);
	} else {
		auto numToCopy = capacity - back;
		memcpy(newData, &data[back], numToCopy);
		memcpy(&newData[numToCopy], data, front + 1);
	}
	delete[] data;
	capacity = newCapacity;
	data = newData;
	back = 0;
	front = numBytes;
}

int dataBuffer::getSize() {
	return numBytes;
}

int dataBuffer::getCapacity() {
	return capacity;
}

void dataBuffer::write(BYTE* d, int size) {
	while (numBytes + size > capacity) {
		resize();
	}
	if (front + size <= capacity) {
		memcpy(&data[front], d, size);
	} else {
		auto preSize = (capacity) - front;
		memcpy(&data[front], d, preSize);
		memcpy(data, (d)+preSize, size - preSize);
	}
	front = (front + size) % capacity;
	numBytes += size;
}

BYTE* dataBuffer::read(int size, int& actualSize) {
	int as;
	if (numBytes == 0) {
		actualSize = 0;
		return NULL;
	} else if (size > numBytes) {
		as = numBytes;
	} else {
		as = size;
	}

	auto readData = new BYTE[as];

	if (back + as <= capacity) {
		memcpy(readData, &data[back], as);
	} else {
		auto preSize = (capacity) - back;
		memcpy(readData, &data[back], preSize);
		memcpy((readData) + preSize, data, as - preSize);
	}
	back = (back + as) % capacity;
	numBytes -= as;
	actualSize = as;
	return readData;
}

void dataBuffer::print() {
	cout << "Printing Data Buffer:" << endl;
	cout << "Cap: " << capacity << endl;
	cout << "Siz: " << numBytes << endl;
	cout << "Front: " << front << " :" << data[front] << endl;
	cout << "Back: " << back << " :" << data[back] << endl;
	cout << "->";
	for (int i = 0; i < capacity; i++) {
		cout << (char)data[i];
	}
	cout << "<-\n\n";
}