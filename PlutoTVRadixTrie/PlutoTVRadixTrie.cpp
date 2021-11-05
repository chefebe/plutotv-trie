// PlutoTVRadixTrie.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// gcc trei.cpp -o trei

#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <tgmath.h>

const int NUM_DIGITS = 10;
const int VERBOSE = false;
/**/
/*
void printNodes(node *pNode, int level=0) {
	printf("%*s%s\n", level, "", pNode->val);
	for (int i = 0; i < pNode->numNodes; i++) {
		printNodes(&(pNode->nodeArray[i]), level + 1);
	}
}
*/

double getMapSize(int multiple) {
	if (multiple >= 0) {
		return pow(10, multiple) + getMapSize(multiple - 1);
	}
	return 0;
}

void fillRandomMap(unsigned char *map, int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		map[i] = i % 256;
	}
}

bool get(unsigned char *map, int idx) {
	int arrayIndex = int(floor(idx / 8));
	int posInByte = idx % 8;
	int arrayVal = map[arrayIndex];
	int bitVal = (arrayVal >> (posInByte)) & 0x1;

	if (VERBOSE) {
		if (posInByte == 0) {
			char binary[9];
			itoa(arrayVal, binary, 2);
			printf("------ New array item: %d [%s] \n", arrayVal, binary);
		}
		printf("Array Index: %d. Array Value: %d. bitPos: %d. bitVal = %d\n", arrayIndex, arrayVal, posInByte, bitVal);
	}
	return (bitVal == 1);
}

void set(unsigned char *map, int idx, bool value) {


}

// using radix trie orgnization, find bit number of this phone number's leaf
double getBitPositionFromPhoneNumber(const char* phoneNumber) {
	int numDigits = strlen(phoneNumber);
	int *nums = new int[numDigits];
	for (int i = 0; i < numDigits; i++) {
		nums[i] = phoneNumber[i] - '0';
	}
	printf("--- Number: %s\n", phoneNumber);
	double triePosition = 0;
	double trieBaseIndex = 0;
	double trieRowOffset = 0;
	for (int level = 0; level < numDigits; level++) {
		trieBaseIndex += (level == 0 ? 0 : pow(10, level));
		trieRowOffset = (level == 0 ? nums[level] : 10 * trieRowOffset + nums[level]);
		triePosition = trieBaseIndex + trieRowOffset;
		printf("level: %d. number: %d. base: %f. offset: %f. position: %f\n", 
			level, nums[level], trieBaseIndex, trieRowOffset, triePosition);
	}
	return triePosition;
}

// 0110 1011

int main()
{
	printf("Go PlutoTV\n");
	
	// array of bits. 10+100+1K+10K+100K+1M+10M+100M+1B+10B == 11,111,111,110
	// integers 8 bits each.  1,388,888,889	

	int arraySize = int(ceil(getMapSize(NUM_DIGITS) / 8.0));
	printf("arraySize: %d\n", arraySize);

	//printf("map 10 size: %f\n", getMapSize(NUM_DIGITS));

	arraySize = 300;
	unsigned char *map = new unsigned char[arraySize];
	// clear all values
	memset(map, 0, arraySize);

	fillRandomMap(map, arraySize);
	for (int i = 0; i < 2400; i++) {
		// print bit values (0,1,2,3)
		bool isSet = get(map, i);
	}

	while (true) {
		printf("Welcome to Chris' Riddle: To Trie or not to Trie\n");
		printf("------------------------\n");
		printf("1) Set or unset a phone number\n");
		printf("2) Get state of phone number\n");
		printf("3) Find phone number that is set or unset\n");
		printf("4) Show phone number bit positions in array\n");
		printf("q) Quit\n");

		char c;
		scanf("%c", &c);

		char phoneNumber[100];
		if (c == 1) {
			printf("Enter 10-digit phone number: ");
			getPhoneNumber(phoneNumber);
			printf("Phone: %s", phoneNumber);
			printf("1) Set\n");
			printf("2) Unset\n");
		}
	}

	return 0;
}

void getPhoneNumber(char *buffer) {
	while (true) {
		scanf("%9s", buffer);
		if (strlen(buffer) != 10) {
			printf("Phone number must be 10 digits");
			continue;
		} 
		char *endptr;
		strtol(buffer, &endptr, 10);
		if (*endptr != '\0' || endptr == buffer) {
			printf("Invalid phone number");
			continue;
		}
		break
	}
}


/*

getBitPositionFromPhoneNumber ("000");
getBitPositionFromPhoneNumber ("001");
getBitPositionFromPhoneNumber ("002");
getBitPositionFromPhoneNumber ("003");
getBitPositionFromPhoneNumber ("004");
getBitPositionFromPhoneNumber ("005");
getBitPositionFromPhoneNumber ("006");
getBitPositionFromPhoneNumber ("007");
getBitPositionFromPhoneNumber ("008");
getBitPositionFromPhoneNumber ("009");

getBitPositionFromPhoneNumber ("010");
getBitPositionFromPhoneNumber ("011");
getBitPositionFromPhoneNumber ("012");
getBitPositionFromPhoneNumber ("013");
getBitPositionFromPhoneNumber ("014");
getBitPositionFromPhoneNumber ("015");
getBitPositionFromPhoneNumber ("016");
getBitPositionFromPhoneNumber ("017");
getBitPositionFromPhoneNumber ("018");
getBitPositionFromPhoneNumber ("019");

getBitPositionFromPhoneNumber ("020");
getBitPositionFromPhoneNumber ("021");
getBitPositionFromPhoneNumber ("022");
getBitPositionFromPhoneNumber ("023");
getBitPositionFromPhoneNumber ("024");
getBitPositionFromPhoneNumber ("025");
getBitPositionFromPhoneNumber ("026");
getBitPositionFromPhoneNumber ("027");

getBitPositionFromPhoneNumber ("028");
getBitPositionFromPhoneNumber ("029");
getBitPositionFromPhoneNumber ("030");
getBitPositionFromPhoneNumber ("031");
getBitPositionFromPhoneNumber ("032");
getBitPositionFromPhoneNumber ("033");
getBitPositionFromPhoneNumber ("034");
getBitPositionFromPhoneNumber ("035");
getBitPositionFromPhoneNumber ("036");
getBitPositionFromPhoneNumber ("037");
getBitPositionFromPhoneNumber("038");
getBitPositionFromPhoneNumber("039");
getBitPositionFromPhoneNumber("040");
getBitPositionFromPhoneNumber("041");

getBitPositionFromPhoneNumber("097");
getBitPositionFromPhoneNumber("098");
getBitPositionFromPhoneNumber("099");
getBitPositionFromPhoneNumber("100");
getBitPositionFromPhoneNumber("101");
getBitPositionFromPhoneNumber("102");
getBitPositionFromPhoneNumber("199");
getBitPositionFromPhoneNumber("200");
getBitPositionFromPhoneNumber("201");
getBitPositionFromPhoneNumber("202");

getBitPositionFromPhoneNumber("298");
getBitPositionFromPhoneNumber("299");
getBitPositionFromPhoneNumber("300");
getBitPositionFromPhoneNumber("301");
getBitPositionFromPhoneNumber("302");
getBitPositionFromPhoneNumber("303");
getBitPositionFromPhoneNumber("999");
getBitPositionFromPhoneNumber("0000");
getBitPositionFromPhoneNumber("0001");

getBitPositionFromPhoneNumber("0999");
getBitPositionFromPhoneNumber("1000");

getBitPositionFromPhoneNumber("1999");
getBitPositionFromPhoneNumber("2000");
getBitPositionFromPhoneNumber("2499");
getBitPositionFromPhoneNumber("2500");

getBitPositionFromPhoneNumber("5899");
getBitPositionFromPhoneNumber("5900");
getBitPositionFromPhoneNumber("5901");
getBitPositionFromPhoneNumber("9009");
getBitPositionFromPhoneNumber("9010");

getBitPositionFromPhoneNumber("8879");
getBitPositionFromPhoneNumber("8880");
	getBitPositionFromPhoneNumber("1234567890");
	getBitPositionFromPhoneNumber("9999999999");
	
	*/
