/* 
*  FILE          : cA4.c
*  PROJECT       : PROG1345 - Assignment #4
*  PROGRAMMER    : Verdi Rodrigues-Diamond
*  FIRST VERSION : 2012-11-12
*  DESCRIPTION   :
*    The functions in this file are used to
*	 calculate the route timesavailable on 
*	 a crazy airline fueled only by Carlo's
*	 imagination (and jet fuel).
*/

#include <stdio.h>
#include <stdlib.h>

#define FALSE			0
#define TRUE			1

#define INPUT_BUF_MAX	80

#define NUM_CITIES		6
#define CITY_OFFSET		1

int checkRange (int input, int rangeMin, int rangeMax);
int getNumNicely( char* question );
int getNum(void);
int getRoute (char *cityNames[], int flyingTimes[], int layoverTimes[], int home, int dest);
void printAirports(char *cityNames[]);
void menu (char **cityNames, int *flyingTimes, int *layoverTimes);
void populateCities (char *cityNames[], int flyingTimes[], int layoverTimes[]);



/*
* FUNCTION : checkRange
* DESCRIPTION :
* This function decides whether a given
* input is within a given maximum and
* minimum range.
* PARAMETERS :
* int input : The value to check
* int rangeMin: Range bottom end or minimum value
* int rangeMax: Range top end or maximum value
* RETURNS :
* int : returns the result of the check. 1 if
* the input is inside the range and 0
* if it is not.
*/
int checkRange (int input, int rangeMin, int rangeMax) {
	// Define and assign the return value to it's false state
	int result = 0;

	// Check whether the input is within the predefined range
	if ( input >= rangeMin && input <= rangeMax ) {

		// Return result as 1 since it is within its range
		result = 1;
	}
	else {
		// Return result as 0 since it is not within its range
		// Since result has been already assigned 0, there is nothing to do here
	}

	return result;
}



/*
* FUNCTION : getNumNicely
* DESCRIPTION :
* This function gets a number from the
* user using getNum() but more nicely.
* PARAMETERS :
* char* question : Question or phrase to print
*				   before reading input
* RETURNS :
* int : returns the result of the getNum() call
*/
int getNumNicely( char* question ) {
	printf("%s\n", question);
	return getNum();
}



/*
* FUNCTION : getNum
* DESCRIPTION :
* This function gets a number from the user
* using stdin
* PARAMETERS :
* void :
* RETURNS :
* int : The number the user entered formatted
* as an integer.
*/
int getNum(void) {
	/* the array is 121 bytes in size; we'll see in a later lecture how we can improve this code */
	char record[INPUT_BUF_MAX] = {0}; /* record stores the string */
	int number = 0;
	/* NOTE to student: indent and brace this function consistent with your others */
	/* use fgets() to get a string from the keyboard */
	fgets(record, INPUT_BUF_MAX, stdin);
	/* extract the number from the string; sscanf() returns a number
	* corresponding with the number of items it found in the string */
	if( sscanf(record, "%d", &number) != 1 ) {
	/* if the user did not enter a number recognizable by
	* the system, set number to -1 */
	number = -1;
	}
	return number;
}



/*
* FUNCTION : getRoute
* DESCRIPTION :
* This function finds a route through this
* crazy airplane company
* PARAMETERS :
* char *cityNames[] : String array of the
*					  names of all of the
*					  populated airports
* int flyingTimes[] : Array of all of the
*					  lengths of flights
*					  in minutes between
*					  airports
* int layoverTimes[] : Array of all the lengths
*					   of layovers between
*					   connecting flights
* int home : ID of the starting airport
*			 (-1 of what Carlo's IDs are 
*			 to not waste the first slot)
* int dest : ID of the ending airport
*			 (-1 of what Carlo's IDs are 
*			 to not waste the first slot)
* RETURNS :
* int : 0 if a route was found
*		1 if the start and end are the same
*		2 if the user tries to go backwards
*/
int getRoute (char *cityNames[], int flyingTimes[], int layoverTimes[], int home, int dest) {
	int result = 0;
	int airplane = home; // Creative name for iterator

	int travelTime = 0; // In minutes
	
	if (home > dest) {

		printf("You can't go backwards.\n");

		// But you could :'(

		/*
		printf("Departing from (#%d) %s for arrival at (#%d) %s\n\n", 
			home + CITY_OFFSET, cityNames[home], dest + CITY_OFFSET, cityNames[dest]);

		printf("Home -> Destination:\tFlying Time:\tLayover Time:\n");
		for( airplane = home; airplane > dest; airplane--) {
			if (airplane == dest + 1) {
				printf("%s -> %s\t%02d:%02d\t\t\n", 
					cityNames[airplane], cityNames[airplane - 1], flyingTimes[airplane - 1] / 60,
					flyingTimes[airplane - 1] % 60);
				travelTime += flyingTimes[airplane];
			}
			else {
				printf("%s -> %s\t%02d:%02d\t\t%02d:%02d\n", 
					cityNames[airplane], cityNames[airplane - 1], flyingTimes[airplane - 1] / 60,
					flyingTimes[airplane - 1] % 60, layoverTimes[airplane - 1] / 60, layoverTimes[airplane - 1] % 60);
				travelTime += flyingTimes[airplane] + layoverTimes[airplane];
			}
		}
		
		printf("Your trip will take %02d:%02d\n", travelTime / 60, travelTime % 60);
		*/

		result = 2;
	}
	else if (home < dest) {
		printf("Departing from (#%d) %s for arrival at (#%d) %s\n\n", 
			home + CITY_OFFSET, cityNames[home], dest + CITY_OFFSET, cityNames[dest]);

		printf("Home -> Destination:\tFlying Time:\tLayover Time:\n");
		for( airplane = home; airplane < dest; airplane++) {
			// Check if this is the last leg of the trip
			if (airplane == dest - 1) {
				// If it is, kick off the layover time as we're not continuing on
				printf("%s -> %s\t%02d:%02d\t\t\n", 
					cityNames[airplane], cityNames[airplane + 1], flyingTimes[airplane] / 60,
					flyingTimes[airplane] % 60);
				// Don't forget to add the minutes of the flight to our total flight length
				travelTime += flyingTimes[airplane];
			}
			else {
				printf("%s -> %s\t%02d:%02d\t\t%02d:%02d\n", 
					cityNames[airplane], cityNames[airplane + 1], flyingTimes[airplane] / 60,
					flyingTimes[airplane] % 60, layoverTimes[airplane] / 60, layoverTimes[airplane] % 60);
				// Don't forget to add the minutes of the flight and layover to our total flight length
				travelTime += flyingTimes[airplane] + layoverTimes[airplane];
			}
		}

		// Display the final trip length
		printf("Your trip will take %02d:%02d:%02d\n", (travelTime / 60) / 24, (travelTime / 60) % 24, travelTime % 60);
	}
	else {
		// Alert the user if their starting and ending cities are the same
		printf("Turn around! You're already there!\n");
		result = 1;
	}
	
	return result;
}



/*
* FUNCTION : printAirport
* DESCRIPTION : 
* Prints all of the populated airports along
* with the airport ids
* PARAMETERS :
* char *cityNames[] : String array of the
*					  names of all of the
*					  populated airports
* RETURNS :
* void :
*/
void printAirports(char *cityNames[]) {
	int i = 0;

	printf("Airports: ");

	// Loop through all of the cities and print out their names
	for (i = 0; i < NUM_CITIES; i++) {
		printf("(#%d) %s ", i + CITY_OFFSET, cityNames[i]);
	}

	printf("\n");
}



/*
* FUNCTION : menu
* DESCRIPTION :
* Provides a menu to the user to select
* starting and ending airports from 
* stdio.
* PARAMETERS :
* char *cityNames[] : String array of the
*					  names of all of the
*					  populated airports
* int flyingTimes[] : Array of all of the
*					  lengths of flights
*					  in minutes between
*					  airports
* int layoverTimes[] : Array of all the lengths
*					   of layovers between
*					   connecting flights
* RETURNS :
* void : 
*/
void menu (char *cityNames[], int flyingTimes[], int layoverTimes[]) {
	int exit = FALSE; // Exit sentinal
	int input = 1; // Input buffer

	int home = 1;
	int destination = 1;

	while(!exit) {
		// Let the user know what airports are available
		printAirports(cityNames);

		input = getNumNicely("Please enter the number of your starting city airport");
		if ( checkRange(input, CITY_OFFSET, NUM_CITIES) ) {
			// Home city is validated
			// Save the home city
			home = input;
		}
		else if (input == 0) {
			// Exit sentinal has been reached
			printf("You entered 0. Now exiting\n");
			exit = TRUE;
			continue;
		}
		else {
			printf("Invalid input. Please try again.\n");
			continue;
		}

		input = getNumNicely("Please enter the number of your ending city airport");
		if ( checkRange(input, CITY_OFFSET, NUM_CITIES) ) {
			// Home city is validated
			// Save the destination city
			destination = input;
		}
		else {
			printf("Invalid input. Please try again.\n");
			continue;
		}

		printf("\n");

		// Print off the route information from the home airport to the destination airport
		getRoute(cityNames, flyingTimes, layoverTimes, home - CITY_OFFSET, destination - CITY_OFFSET);

		printf("\n\n");
	}
}



int main (void) {

	// Populate the darn buffers
	char *cityNames [NUM_CITIES] = {
		"Toronto",
		"Atlanta",
		"Austin",
		"Denver",
		"Chicago",
		"Buffalo"
	};

	int flyingTimes [NUM_CITIES - 1] = {
		(4 * 60) + 15,
		(3 * 60) + 58,
		(3 * 60) + 55,
		(2 * 60) + 14,
		(3 * 60) + 27
	};

	int layoverTimes [NUM_CITIES - 1] = {
		(1 * 60) + 20,
		(0 * 60) + 46,
		(11 * 60) + 29,
		(0 * 60) + 53,
		0
	};

	//populateCities(cityNames, flyingTimes, layoverTimes);


	menu(cityNames, flyingTimes, layoverTimes);

	// Don't forget to free your memory :)
	free(cityNames);
	free(flyingTimes);
	free(layoverTimes);


	return 0;
}