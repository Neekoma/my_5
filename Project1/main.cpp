#include<iostream>
#include"files.h"

#define TXT_FILE "source.txt"
#define BIN_FILE "bin.myfile"
#define INDEX_FILE "indexfile.ind"

int main() {
	writeBin(TXT_FILE, BIN_FILE);
	indexFile(BIN_FILE, INDEX_FILE);
	std::cout << "\nНайденная запись: " << getRecord("5347-9076", INDEX_FILE, BIN_FILE).name;
	return 0;
}