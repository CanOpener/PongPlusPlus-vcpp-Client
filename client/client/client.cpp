#include "stdafx.h"
#include <cstdint>
#include <SDL_net.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include "binaryConverter.h"
#include "Messages.h"
#include "dataBuffer.h"
using namespace std;

void print(int size, dataBuffer& db) {
	cout << "Reading size: " << size << endl;
	int num;
	auto data = db.read(size, num);
	cout << "Read result ->";
	for (int i = 0; i < num; i++) {
		cout << data[i];
	}
	cout << "<- actualSize: " << num << endl;
	db.print();
}
void write(string s, dataBuffer& db) {
	cout << "Writing string: " << s << endl;
	auto str = s.c_str();
	auto data = new BYTE[s.size()];
	auto seeker = data;
	binaryConverter::writeString(&seeker, s);
	db.write(data, s.size());
	db.print();
}

int main(int argc, char *argv[])
{
	dataBuffer db(3);
	write("Hello!", db);
	print(3, db);
	write("Add", db);
	write("e", db);
	print(2, db);
	write("SMHASIPZ", db);
	return 0;
}



