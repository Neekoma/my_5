#pragma once

#include <string>

struct enterprise {
	int k;
	char license[9];
	char name[45];
	char founder[45];

	int key() {
		int sumA = 0;
		int sumB = 0;
		
		for (int i = 0; i < 9; i++) {
			if (license[i] != '-' && i < 4) {
				sumA += license[i] - ' ';
			}
			else if(license[i] != '-' && i > 4) {
				sumB += license[i] - ' ';
			}
		}

		sumA*= sumB;
		return sumA;
	}
	
	int key(std::string l) {
		int sumA = 0;
		int sumB = 0;

		for (int i = 0; i < 9; i++) {
			if (l[i] != '-' && i < 4) {
				sumA += l[i] - ' ';
			}
			else if (l[i] != '-' && i > 4) {
				sumB += l[i] - ' ';
			}
		}

		sumA *= sumB;
		return sumA;
	}
};