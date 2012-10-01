
/* Assignment #1B
 * Name: Verdi R-D
 * Date: Sept 6th, 2012
 * Comment: I don't know C. This was just me playing around
 */

#include <stdio.h>
#include <stdlib.h>

// Enable for debug output. Lets you trace a stack trace more easily.
#define DEBUG 0

// Preferrably not handled by the precompiler but I also didn't want to hard code it.
#define NUM_BRIEFCASES 26

int numbriefcases = 26;
int bankerRounds = 6;

struct briefcase {
	// Money inside the briefcase
	int amount;

	// C doesn't natively support booleans... Why I don't understand
	int opened;
};

void populatebriefcases (struct briefcase briefcases [], int numbriefcases) {
	int i;

	srand(1);

	if (DEBUG) printf("briefcases:\r\n");
	for (i = 0; i < numbriefcases; i++ ) {
		briefcases[i].amount = rand();
		briefcases[i].opened = 0;
		if (DEBUG) printf("Suitecase %d: %d\r\n", i + 1, briefcases[i].amount);
	}

	return;
}

void printClosedBriefcases (struct briefcase briefcases [], int numbriefcases) {
	int x;

	for (x = 0; x < numbriefcases; x++) {
		// If the briefcase is closed, print it's number
		if (briefcases[x].opened == 0) printf("%d ", x + 1);
	}
}

int checkBriefcase (struct briefcase briefcases[], int briefcase) {
	if (!briefcases[briefcase].opened) return 1;
	else return 0;
}

void openBriefcase (struct briefcase briefcases[], int briefcase) {
	briefcases[briefcase - 1].opened = 1;
	printf("There is %d in briefcase %d", briefcases[briefcase -1].amount, briefcase);
	return;
}

int getInt (char * question) {
	int answer = 0;
	do {
		printf("%s: ", question);
		answer = getNum();
		printf("\r\n");
	} while (!answer);

	return 0;
}

int getYesNo (char * question) {
	char* answer;
	do {
		printf("%s [y/n]: ", question);
		sscanf(answer, "%c");
		printf("\r\n");
	} while (0);

	return 0;
}

int gameLoop (struct briefcase briefcases [], int numbriefcases) {
	int sum = 0;
	int roundSum = 0;
	int selectedBriefcase = 0;

	int x;
	int y;

	for (x = bankerRounds; x > 0; x--) {
		for (y = 0; y < x; y++) {
			// Open some briefcases
			printf("Briefcases left: ");
			printClosedBriefcases(briefcases, NUM_BRIEFCASES);
			printf("\r\n");

			selectedBriefcase = getInt("Which briefcase would you like to open?");
			printf("%d\r\n", selectedBriefcase);
			if (checkBriefcase(briefcases, selectedBriefcase)) openBriefcase(briefcases, selectedBriefcase);




		}
		// Banker makes an offer

	}

	return 0;
}

void startGame (void) {
	struct briefcase briefcases [NUM_BRIEFCASES];
	populatebriefcases(briefcases, NUM_BRIEFCASES);

	gameLoop(briefcases, NUM_BRIEFCASES);

}


// Straight from the page
int getNum(void)
{

	/* the array is 121 bytes in size; we'll see in a later lecture how we can improve this code */
	char record[121] = {0};                      /*  record stores the string */
	int number = 0;

	/* NOTE to  student: indent and brace this function consistent with  your others */
	/* use  fgets() to get a string from the keyboard */
	fgets(record,  121, stdin);

	/* extract  the number from the string; sscanf() returns a number 
	* corresponding with the number of items it found in the string */
	if(  sscanf(record, "%d", &number) != 1 )
	{
		/*  if the user did not enter a number recognizable by 
			* the system, set number to -1 */
		number  = -1;
	}

	return  number;
}


int main (void) {
	startGame();

	return 0;
}