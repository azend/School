/*
* FILE : mini3.c
* PROJECT : PROG1345 - Mini Assignment #3
* PROGRAMMER : Verdi R-D
* FIRST VERSION : 2012-11-29
* DESCRIPTION :
* This program takes a date from the user
* and then outputs the date in a reordered
* format.
*/

#include <stdio.h>

#include "mini3_proto.h"

// Original fix for sscanf being depreciated in Visual Studio
//#pragma warning (disable: 4996) // Remove the warning for using the now depreciated sscanf over the microsoft version

// Probably a better solution
#define sscanf sscanf_s



int main (void) {
	int result = 0;

	// Define your data structure and input buffer
	struct MyDate birthday = {0};
	char birthdayInput [BIRTHDAY_INPUT_BUFFER_SIZE] = {0};

	// Get the birthday from the user
	printf("Please enter a birthday in format MMM DD YYYY: ");

	if ( fgets(birthdayInput, BIRTHDAY_INPUT_BUFFER_SIZE, stdin) != NULL ) {

		// Check that it is in the correct format and pop it into our data structure
		if ( sscanf(birthdayInput, "%3s %2d %4d", birthday.month, &birthday.day, &birthday.year) == NUM_MYDATE_FIELDS ) {

			// If it is, use our data structure to reformat the text in a different way
			printf("The birthday reformatted is: %4d/%3s/%2d\n", birthday.year, birthday.month, birthday.day);
		}
		else {
			// Either the user did not enter enough information or did not do it in the format specified
			printf("ERROR: You did not insert information in the correct format\n");
			result = 2;
		}

	}
	else {
		// Something went wrong while reading input from the user
		printf("ERROR: An error occurred while reading your input\n");
		result = 1;
	}

	return result;
}