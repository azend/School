

#include <stdio.h>

#define FALSE	0
#define TRUE	1

#define NUM_CITIES	6


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
	char record[121] = {0}; /* record stores the string */
	int number = 0;
	/* NOTE to student: indent and brace this function consistent with your others */
	/* use fgets() to get a string from the keyboard */
	fgets(record, 121, stdin);
	/* extract the number from the string; sscanf() returns a number
	* corresponding with the number of items it found in the string */
	if( sscanf(record, "%d", &number) != 1 ) {
	/* if the user did not enter a number recognizable by
	* the system, set number to -1 */
	number = -1;
	}
	return number;
}

int getRoute (char *cityNames[], int flyingTimes[], int layoverTimes[], int home, int dest) {
	int airplane = home; // Creative name for iterator

	printf("Departing from %s for arrival at %s\n", cityNames[home], cityNames[dest]);
	
	for( airplane = home; airplane < dest; airplane++) {
		printf("%s -> %s - Flying time: %02d:%02d - Layover time: %02d:%02d", 
			cityNames[airplane], cityNames[airplane + 1], flyingTimes[airplane] / 60,
			flyingTimes[airplane] % 60, layoverTimes[airplane] / 60, layoverTimes[airplane] % 60);
	}

}

void menu (void) {
	int exit = FALSE;

	int input = 1;

	while(!exit) {
		input = getNumNicely("Please enter home city airport");
		if (input == 0) {
			break;
		}
	}
}

void populateCities (char *cityNames, int *flyingTimes, int *layoutTimes) {

	char *cityNamesBuffer [NUM_CITIES] = {
		"Toronto",
		"Atlanta",
		"Austin",
		"Denver",
		"Chicago",
		"Buffalo"
	};

	int flyingTimesBuffer [NUM_CITIES] = {
		(4 * 60) + 15,
		(3 * 60) + 58,
		(3 * 60) + 55,
		(2 * 60) + 14,
		(3 * 60) + 27,
		0
	};

	int layoverTimesBuffer[NUM_CITIES] = {
		(1 * 60) + 20,
		(0 * 60) + 46,
		(11 * 60) + 29,
		(0 * 60) + 53,
		0,
		0
	};

	cityNames = cityNamesBuffer;

}

int main (void) {
	char *cityNames;





	//menu();

	getRoute(0, 3);

	return 0;
}