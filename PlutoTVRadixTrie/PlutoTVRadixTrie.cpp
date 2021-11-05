// PlutoTVRadixTrie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// gcc trei.cpp -o trei

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <tgmath.h>

const int NUM_DIGITS = 10;
enum flag {GET_IDX, SET, UNSET, FIND_SET, FIND_UNSET};

double getMapSize(int multiple) {
	if (multiple >= 0) {
		return pow(10, multiple) + getMapSize(multiple - 1);
	}
	return 0;
}

void binaryStr(int val, char *buf, int bufLength) {
	char binaryStr[9];
	itoa(val, binaryStr, 2);
	int padLength = bufLength - int(strlen(binaryStr));
	for (int i = 0; i < bufLength; i++) {
		buf[i] = (i < padLength ? '0' : binaryStr[i-padLength]);
	}
	buf[bufLength] = '\0';
}

bool get(unsigned char *map, double idx) {
	int arrayIndex = int(floor(idx / 8));
	int posInByte = int(fmod(idx, 8)); //idx % 8;
	int arrayVal = map[arrayIndex];
	int bitVal = (arrayVal >> (posInByte)) & 0x1;

	char binStr[9];
	binaryStr(arrayVal, binStr, 8);
	printf("Leaf bit position: %.0lf. Array Index: %d. Array Value: %d (%s). bitPos: %d. bitVal = %d\n", 
		idx, arrayIndex, arrayVal, binStr, posInByte, bitVal);
	return (bitVal == 1);
}

void set(unsigned char *map, double idx, bool value) {

	int arrayIndex = int(floor(idx / 8));
	int posInByte = int(fmod(idx, 8));
	int arrayVal = map[arrayIndex];

	printf("Before:\n");
	bool isSet = get(map, idx);

	if (value) {
		if (isSet) {
			printf("Value already SET\n");
		}
		map[arrayIndex] |= (0x1 << posInByte);
	} else {
		if (!isSet) {
			printf("Value is already NOT SET\n");
		}
		map[arrayIndex] &= ~(0x1 << posInByte);
	}
	if (isSet && !value || !isSet && value) {
		// a change was made. Show new value
		printf("After:\n");
		get(map, idx);
	}
	printf("\n");
}

void find(unsigned char *map, bool isSet, char *buf, int bufLength) {
	printf("Find todo. Navigate tree.");
	strcpy(buf, "0000000000");
}

// using radix trie orgnization, find bit number of this phone number's leaf
double navigateTrie(unsigned char *map, const char* phoneNumber, enum flag action, bool display = false) {
	int numDigits = strlen(phoneNumber);
	int *nums = new int[numDigits];
	for (int i = 0; i < numDigits; i++) {
		nums[i] = phoneNumber[i] - '0';
	}
	// printf("--- Number: %s\n", phoneNumber);
	double triePosition = 0;
	double trieBaseIndex = 0;
	double trieRowOffset = 0;
	for (int level = 0; level < numDigits; level++) {
		trieBaseIndex += (level == 0 ? 0 : pow(10, level));
		trieRowOffset = (level == 0 ? nums[level] : 10 * trieRowOffset + nums[level]);
		triePosition = trieBaseIndex + trieRowOffset;

		if (display) {
			printf("level: %d. number: %d. base: %.0lf. offset: %.0lf. position: %.0lf\n",
				level, nums[level], trieBaseIndex, trieRowOffset, triePosition);
		}
		if (action == SET || action == UNSET) {
			set(map, triePosition, action == SET);
		}
	}
	return triePosition;
}

char getMenuSelect(char *prompt, const char *allowedKeys) {
	printf(prompt);
	char c;
	while (true) {
		scanf("%c", &c);
		if (strchr(allowedKeys, c) != NULL) {
			return c;
		}
	}
	return 0;
}

void getPhoneNumber(char *buffer) {
	while (true) {
		printf("\nEnter 10-digit phone number: ");

		scanf("%100s", buffer);
		if (strlen(buffer) != 10) {
			printf("Phone number must be 10 digits\n");
			continue;
		}
		char *endptr;
		strtol(buffer, &endptr, 10);
		if (*endptr != '\0' || endptr == buffer) {
			printf("Invalid phone number\n");
			continue;
		}
		break;
	}
}

void userInteraction(unsigned char *map) {
	printf("\n\nChris' Challenge: To Trie or not to Trie\n"
		"------------------------\n");
	char prompt[256];
	while (true) {
		strcpy(prompt, "\n"
			"1) Set or unset a phone number\n"
			"2) Get state of phone number\n"
			"3) Find phone number that is set or unset\n"
			"4) Show phone number bit positions in array\n"
			"q) Quit\n");

		char menuSel = getMenuSelect(prompt, "1234q");
		if (menuSel == 'q') {
			break;
		}
		if (menuSel == '3') {
			strcpy(prompt, "\n1) Find a number that is SET\n2) Find a number that is NOT SET\nr) Return to menu\n");
			menuSel = getMenuSelect(prompt, "12r");
			char foundNumBuf[11];
			bool isSet = (menuSel == '1');
			find(map, isSet, foundNumBuf, 10);
			printf("The number %s is %s\n\n", foundNumBuf, (isSet ? "SET" : "NOT SET"));
			continue;
		}

		char phoneNumber[100];
		getPhoneNumber(phoneNumber);
		if (menuSel == '1') {
			strcpy(prompt, "\n1) Set\n2) Unset\nr) Return to menu\n");
			menuSel = getMenuSelect(prompt, "12r");
			if (menuSel == '1' or menuSel == '2') {
				// navigate the trie with set value will set/unset each node as it descends
				navigateTrie(map, phoneNumber, (menuSel == '1' ? SET : UNSET));
			}
		} else if (menuSel == '2') {
			double idx = navigateTrie(map, phoneNumber, GET_IDX);
			bool isSet = get(map, idx);
			printf("The phone number is %s\n\n", (isSet ? "SET" : "NOT SET"));
		} else if (menuSel == '4') {
			navigateTrie(map, phoneNumber, GET_IDX, true);
		}
	}
}

int main()
{
	printf("Go PlutoTV\n");

	// array of bits. 10+100+1K+10K+100K+1M+10M+100M+1B+10B == 11,111,111,110
	// integers 8 bits each.  1,388,888,889	

	int arraySize = int(ceil(getMapSize(NUM_DIGITS) / 8.0));
	printf("arraySize: %d\n", arraySize);
	arraySize = 1000000000;
	unsigned char *map = new unsigned char[arraySize];
	printf("map created!");
	memset(map, 0xF, arraySize);  // change 0xF to 0 to start fully unset. This sets every 1/2 byte for testing

	userInteraction(map);
	return 0;
}
