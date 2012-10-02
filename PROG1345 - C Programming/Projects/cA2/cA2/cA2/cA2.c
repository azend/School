
/* 
 *  FILE          : cA2.c
 *  PROJECT       : PROG1345 - Assignment #2
 *  PROGRAMMER    : Verdi R-D
 *  FIRST VERSION : 2012-09-25
 *  DESCRIPTION   :
 *    The functions in this file are used to calculate the
 *    power of a given number by it's exponent and to check
 *    whether a number is within a given range.
 */

#include <stdio.h>

// Pre-compiler defined debug condition. Only really useful for me (author).
#define DEBUG 0

//
// FUNCTION PROTOTYPES
//
int checkRange (int input, int rangeMin, int rangeMax);
int feelThePower(int base, int exponent);
int getNum(void);
int main (void);

/*
 * FUNCTION      : checkRange
 * DESCRIPTION   :
 *   This function decides whether a given
 *   input is within a given maximum and 
 *   minimum range.
 * PARAMETERS    :
 *   int input   : The value to check
 *   int rangeMin: Range bottom end or minimum value
 *   int rangeMax: Range top end or maximum value
 * RETURNS       :
 *   int : returns the result of the check. 1 if
 *            the input is inside the range and 0
 *            if it is not.
 */
int checkRange (int input, int rangeMin, int rangeMax) {
	// Define and assign the return value to it's false state
	int result = 0;

	// Check whether the input is within the predefined range
	if ( input >= rangeMin && input <= rangeMax ) {
		if (DEBUG) printf("%d is inside the range of %d to %d\r\n", input, rangeMin, rangeMax);

		// Return result as 1 since it is within its range
		result = 1;
	}
	else {
		// Return result as 0 since it is not within its range
		if (DEBUG) printf("%d is not inside the range of %d to %d\r\n", input, rangeMin, rangeMax);
		// Since result has been already assigned 0, there is nothing to do here
	}

	return result;
}

/*
 * FUNCTION      : feelThePower
 * DESCRIPTION   :
 *   This function calculates an algebraic
 *   power using a passed base and exponent.
 * PARAMETERS    :
 *   int base    : The power's base
 *   int exponent: Power's exponent
 * RETURNS       :
 *   int : total after performing an algebraic
 *            power function using the passed
 *            base and exponent.
 */
int feelThePower(int base, int exponent) {
	int result = 1;
	int i = 0;

	result = base;
	
	for (i = 0; i < exponent - 1; i++) {
		result *= base;
	}

	return result;
}



/*
 * FUNCTION      : getNum
 * DESCRIPTION   :
 *   This function gets a number from the user
 *   using stdin
 * PARAMETERS    :
 *   void        : 
 * RETURNS       :
 *   int : The number the user entered formatted
 *            as an integer.
 */
int getNum(void) {
	/* the array is 121 bytes in size; we'll see in a later lecture how we can improve this code */
	char record[121] = {0};                      /*  record stores the string */
	int number = 0;
	/* NOTE to  student: indent and brace this function consistent with  your others */
	/* use  fgets() to get a string from the keyboard */
	fgets(record,  121, stdin);
	/* extract  the number from the string; sscanf() returns a number 
	* corresponding with the number of items it found in the string */
	if(  sscanf(record, "%d", &number) != 1 ) {
		/*  if the user did not enter a number recognizable by 
		* the system, set number to -1 */
		number  = -1;
	}
	return  number;
}

int main (void) {
	// Assign default values to variables base and exponent
	// (I picked 5 and 2 as defaults because I felt like it)
	int base = 5, exponent = 2;

	// Create an exit condition for when the user tries to exit
	int exiting = 0;
	
	// Create an input buffer for deciding whether or not to 
	// use inputted values
	int input = 0;

	while (!exiting) {
		printf("Power Menu:\n");
		printf("\t1. Change base\n");
		printf("\t2. Change exponent\n");
		printf("\t3. Display base raised to exponent\n");
		printf("\t4. Exit Program\n");
		printf("\n");
		printf("Option? ");

		input = getNum();

		if (checkRange(input, 1, 4)) {
			switch (input) {
			case 1:
				// Get the base from the user
				printf("Please enter a base: ");
				input = getNum();

				// Check if it is between our preset range
				if (checkRange(input, 1, 25)) {
					// If it is, make it our base
					base = input;
				}
				else {
					// If it isn't, ignore it and use default values
					printf("The value %d is out of range. Defaulting to %d\r\n", input, base);
				}
				break;

			case 2:
				// Get the base from the user
				printf("Please enter an exponent: ");
				input = getNum();

				// Check if it is between our preset range
				if (checkRange(input, 1, 5)) {
					// If it is, make it our base
					exponent = input;
				}
				else {
					// If it isn't, ignore it and use default values
					printf("The value %d is out of range. Defaulting to %d\r\n", input, exponent);
				}
				break;

			case 3:
				// Print the calculated power
				printf("%d to the power of %d is %d\r\n\r\n", base, exponent, feelThePower(base, exponent));
				break;

			case 4:
				printf("Exiting...");
				exiting = 1;
				break;
			}
		}
		else {
			printf("Invalid input.\n");
		}

		
		printf("\n");	
	}
}