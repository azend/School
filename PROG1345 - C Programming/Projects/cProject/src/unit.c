
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "unit.h"

#define TEST_PASSED	1
#define TEST_FAILED	0

char * testErrorMessage = "";

int testChar ( char input, char expected ) {
	int testResult = TEST_FAILED;
	
	if ( input == expected ) {
		testResult = TEST_PASSED;
	}
	else {
		sprintf(testErrorMessage, "Char %c does not match %c\n", input, expected);
	}

	return testResult;
}

int testInt ( int input, int expected ) {
	int testResult = TEST_FAILED;
	
	if ( input == expected ) {
		testResult = TEST_PASSED;
	}
	else {
		sprintf(testErrorMessage, "Int %d does not match %d\n", input, expected);
	}


	return testResult;
}

int testLong ( long input, long expected ) {
	int testResult = TEST_FAILED;
	
	if (input == expected) {
		testResult = TEST_PASSED;
	}
	else {
		sprintf(testErrorMessage, "Long %ld does not match %ld\n", input, expected);
	}
	
	return testResult;
}

int testIntArray ( int input[], int inputLength, int expected[], int expectedLength ) {
	int testResult = TEST_PASSED;
	int i = 0;

	if (inputLength == expectedLength) {
		for (i = 0; i < expectedLength; i++) {
			if (input[i] != expected[i]) {
				sprintf(testErrorMessage, "Input array at element [%d] = %d does not match expected array element[%d] = %d\n", i, input[i], i, expected[i]);
				testResult = TEST_FAILED;
				break;
			}
		}
	}
	else {
		sprintf(testErrorMessage, "Input array length does not match expected array length\n");
		testResult = TEST_FAILED;
	}
	
	return testResult;
	
}

int testString ( char * input, char * expected ) {
	int testResult = TEST_FAILED;

	if ( strcmp( input, expected ) == 0 ) {
		testResult = TEST_PASSED;
	}
	else {
		sprintf(testErrorMessage, "String %s does not match %s\n", input, expected);	
	}

	return testResult;	
}


void printTest ( char* testName, int testResult ) {
	if (testResult == TEST_PASSED) {
		printf("%s\t[PASS]\n", testName);
	}
	else {
		printf(
			"%s\t[FAIL]\n"
			"\t%s\n",
			testName, testErrorMessage
		);
	}
	
	testErrorMessage = "";
}
