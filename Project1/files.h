#pragma once

#include<string>
#include<xtree>
#include<iostream>
#include<fstream>
#include"enterprise.h"
#include"tree.h"

#define END_RECORD 0xFA

using std::string;
using std::ifstream;
using std::ofstream;

int writeIndexFile(ofstream& out, node* n, int recordNumber = 0);

void writeBinTree(ofstream& out, node* n) {
	
	out.write((char*)&n->data, sizeof(enterprise));

	if (n->left) {
		writeBinTree(out, n->left);
	}

	if (n->right) {
		writeBinTree(out, n->right);
	}
}

void writeBin(string txtF, string binF)
{
	ifstream in(txtF);
	ofstream out;
	node* tree = nullptr;
	enterprise e;
	const size_t size = sizeof(enterprise);

	if (!in.is_open())
		exit(-1);

	out.open(binF, std::ios::binary);

	while (!in.eof()) {
		in >> e.license >> e.name >> e.founder;
		e.k = e.key();
		tree = insert(tree, e.k, e);
	}
	writeBinTree(out, tree);
	out.close();
	in.close();
}

void indexFile(string binF, string indexF) {
	typedef void (*func)(node*);
	func indexFunc = nullptr;
	node* tree = nullptr;
	ifstream in(binF, std::ios::binary);
	ofstream out;
	enterprise e;

	if (!in.is_open())
		exit(-1);

	while (in.read((char*)&e, sizeof(enterprise))) {
		tree = insert(tree, e.key(), e);
	}
	std::cout << "Дерево:\n\n";
	print(tree, 8);
	std::cout << "\n\nВставка:\n\n";

	in.close();
	out.open(indexF, std::ios::binary);

	writeIndexFile(out, tree);

	out.close();
}

int writeIndexFile(ofstream& out, node* n, int recordNumber) {
	
	if (!n)
		return -1;

	indexNode iNode;
	iNode.key = n->key;
	iNode.number = recordNumber;
	
	out.write((char*)&iNode, sizeof(indexNode));

	if (n->left) {
		iNode.left = writeIndexFile(out, n->left, ++recordNumber);
	}

	if (n->right) {
		if(iNode.left != -1)
			iNode.right = writeIndexFile(out, n->right, ++recordNumber + 1);
		else
			iNode.right = writeIndexFile(out, n->right, ++recordNumber);
	}
	

	if (iNode.left != -1)
		recordNumber--;
	if (iNode.right != -1)
		recordNumber--;

	out.seekp(recordNumber * sizeof(iNode));

	out.write((char*)&iNode, sizeof(indexNode));
	std::cout << iNode.key << " " << iNode.number << std::endl;
	return recordNumber;
}

enterprise getRecord(string license, string indexF, string binF) {
	ifstream in(indexF, std::ios::binary);
	enterprise e;
	indexNode iNode;
	in.read((char*)&iNode, sizeof(indexNode));
	int key = e.key(license);
	
	while (e.key(license) != iNode.key) {
		if (e.key() < iNode.key) {
			in.seekg(iNode.left * sizeof(iNode));
		}
		else {
			in.seekg(iNode.right * sizeof(iNode));
		}
		in.read((char*)&iNode, sizeof(indexNode));
	}

	in.close();
	in.open(binF, std::ios::binary);
	in.seekg(iNode.number * sizeof(enterprise));
	in.read((char*)&e, sizeof(enterprise));
	in.close();
	return e;
}




