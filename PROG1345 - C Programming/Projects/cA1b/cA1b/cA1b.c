
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

const int kNumBriefcases = 26;
const int kBankerRounds = 6;

/*
 * Convieniently, I haven't had to explicitly make prototypes for this game. If I were 
 * to however, they would go here
 */
void populatebriefcases (struct briefcase briefcases [], int kNumBriefcases);
void printClosedBriefcases (struct briefcase briefcases [], int kNumBriefcases);
int getNumClosedBriefcases (struct briefcase briefcases [], int kNumBriefcases);
int checkBriefcase (struct briefcase briefcases[], int briefcase);
float openBriefcase (struct briefcase briefcases[], int briefcase);
int getInt (char * question);
int getYesNo (char * question);
int pickInitialBriefcase (struct briefcase briefcases [], int kNumBriefcases);
int gameLoop (struct briefcase briefcases [], int kNumBriefcases);
void endGame (int result);
void startGame (void);
int getNum(void);
char getChar(void);


struct briefcase {
	// Money inside the briefcase
	float amount;

	// C doesn't natively support booleans... Why I don't understand
	int opened;
};

void populatebriefcases (struct briefcase briefcases [], int kNumBriefcases) {
	// Terrible names for generic iterators
	int i = 0, x = 0;

	int duplicate = 0;
	int random = 0;

	float briefcaseAmounts [NUM_BRIEFCASES] = {0.01, 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 5000, 10000, 25000, 50000, 75000, 100000, 200000, 300000, 400000, 500000, 750000, 1000000};
	int briefcaseOrder [NUM_BRIEFCASES];


	// Initialize array to -1
	for (i = 0; i < NUM_BRIEFCASES; i++) {
		briefcaseOrder[i] = -1;
	}

	// Randomly generate numbers in an array to be used as ids for the actual briefcase sorting
	srand(1);

	for (i = 0; i < NUM_BRIEFCASES; i++) {
		do {
			duplicate = 0;

			// Generate a new random
			random = rand() % 26;
			
			// Check for duplicates
			for (x = 0; x < NUM_BRIEFCASES; x++) {
				// If there is, regenerate
				if (briefcaseOrder[x] == random) {
					duplicate = 1;
				}
			}
		} while (duplicate);
		briefcaseOrder[i] = random;
	}

	// Build array based on order and amounts
	for (i = 0; i < NUM_BRIEFCASES; i++) {
		briefcases[i].amount = briefcaseAmounts[briefcaseOrder[i]];
		briefcases[i].opened = 0;
	}


	if (DEBUG) printf("briefcases:\r\n");
	for (i = 0; i < kNumBriefcases; i++ ) {
		if (DEBUG) {
			printf("Suitecase %d: %d\r\n", i + 1, briefcases[i].amount);
		}
	}

	return;
}

void printClosedBriefcases (struct briefcase briefcases [], int kNumBriefcases) {
	int x;

	for (x = 0; x < kNumBriefcases; x++) {
		// If the briefcase is closed, print it's number
		if (briefcases[x].opened == 0) {
			printf("%d ", x + 1);
		}
	}
}

int getNumClosedBriefcases (struct briefcase briefcases [], int kNumBriefcases) {
	int x = 0;
	int numClosedBriefcases = 0;

	for (x = 0; x < kNumBriefcases; x++) {
		if (!briefcases[x].opened) {
			numClosedBriefcases++;
		}
	}
	
	return numClosedBriefcases;
}

int checkBriefcase (struct briefcase briefcases[], int briefcase) {
	int result = 0;

	if (!briefcases[briefcase - 1].opened) {
		return 1;
	}

	return result;
}

float openBriefcase (struct briefcase briefcases[], int briefcase) {
	briefcases[briefcase - 1].opened = 1;
	if (DEBUG) printf("There is $%d in briefcase %d\r\n", briefcases[briefcase -1].amount, briefcase);

	return briefcases[briefcase -1].amount;
}

int getInt (char * question) {
	int answer = 0;
	do {
		printf("%s: ", question);
		answer = getNum();
		printf("\r\n");
	} while (!answer);

	return answer;
}

int getYesNo (char * question) {
	char answer;
	do {
		printf("%s [y/n]: ", question);
		answer = getChar();
		printf("\r\n");
	} while (answer != 'y' && answer != 'n');

	if (answer == 'y') {
		return 1;
	}

	else return 0;
}

int pickInitialBriefcase (struct briefcase briefcases [], int kNumBriefcases) {
	int selectedBriefcase = -1;

	while (selectedBriefcase == -1) {
		printf("Briefcases: ");
		printClosedBriefcases(briefcases, NUM_BRIEFCASES);
		printf("\r\n");

		selectedBriefcase = getInt("Which briefcase would you like to pick?");

		// Check if the briefcase exists and has not been opened yet
		if (checkBriefcase(briefcases, selectedBriefcase)) {
			openBriefcase(briefcases, selectedBriefcase);
		}
		else {
			// If not, re ask the question
			selectedBriefcase = -1;
		}
	}
	return selectedBriefcase;
}

int gameLoop (struct briefcase briefcases [], int kNumBriefcases) {
	int result = 0;
	int initialBriefcase = 0;
	double sum = 0;
	double roundSum = 0;
	float briefcaseAmount = 0;
	double bankerOffer = 0;
	int selectedBriefcase = 0;

	int x = 0;
	int y = 0;

	initialBriefcase = pickInitialBriefcase(briefcases, NUM_BRIEFCASES);

	for (x = kBankerRounds; x > 0; x--) {
		roundSum = 0;
		if (DEBUG) printf("The variable x is: %d\n", x);
		for (y = 0; y < x; y++) {
			if (DEBUG) printf("The variable y is: %d\n", y);
			// Open some briefcases
			printf("Briefcases left: ");
			printClosedBriefcases(briefcases, NUM_BRIEFCASES);
			printf("Your case: #%d\r\n", initialBriefcase + 1);
			printf("\r\n");

			selectedBriefcase = getInt("Which briefcase would you like to open?");

			// Check if the briefcase exists and has not been opened yet
			if (checkBriefcase(briefcases, selectedBriefcase)) {
				briefcaseAmount = openBriefcase(briefcases, selectedBriefcase);

				roundSum += briefcaseAmount;
				printf("The briefcase contains $%.2f\r\n", briefcaseAmount);

				printf("\r\n");
			}
			else {
				// If not, re ask the question
				printf("Invalid briefcase.\r\n");
				y--;
			}
			
		}

		sum += roundSum;

		// Banker makes an offer
		printf("The Banker is making an offer ...\r\n");
		bankerOffer = roundSum / x;
		printf("The offer is ... $%.2f\r\n", bankerOffer);
		printf("\r\n");
		if (getYesNo("Would you like to accept the bankers offer")) {
			result = 1;
			break;
		}
		else {
			// Last minute hack to fix the original bad math
			if (DEBUG) printf("There are %d briefcases left in play\n", getNumClosedBriefcases(briefcases, NUM_BRIEFCASES));
			if (getNumClosedBriefcases(briefcases, NUM_BRIEFCASES) && x == 1) x++;
		}

		system("cls");
		
		// Check if the player has accepted the bankers offer and ended the game
		if (result) {
			break;
		}
	}

	if (!result) {
		printf("You stuck with it until the end.. Let's see how well it paid off\r\n");
		printf("Your briefcase, number %d, contains.. $%.2f", initialBriefcase + 1, briefcases[initialBriefcase].amount);
	}

	return result;
}

void endGame (int result) {
	switch (result) {
	case 1:
		printf("You've accepted the bankers offer.");
		break;
	default:
		printf("You lose");
	}
	
}

void startGame (void) {
	int result;

	struct briefcase briefcases [NUM_BRIEFCASES];
	populatebriefcases(briefcases, NUM_BRIEFCASES);

	result = gameLoop(briefcases, NUM_BRIEFCASES);
	
	endGame(result);
}


/*
 * Boilerplate get an integer from prompt code.
 * Straight from the assignment page.
 */
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

// Straight from the page
char getChar(void)
{

	/* the array is 121 bytes in size; we'll see in a later lecture how we can improve this code */
	char record[121] = {0};                      /*  record stores the string */
	char character = 0;

	/* NOTE to  student: indent and brace this function consistent with  your others */
	/* use  fgets() to get a string from the keyboard */
	fgets(record,  121, stdin);

	/* extract  the number from the string; sscanf() returns a number 
	* corresponding with the number of items it found in the string */
	if(  sscanf(record, "%c", &character) != 1 )
	{
		/*  if the user did not enter a number recognizable by 
			* the system, set number to -1 */
		character  = -1;
	}

	return  character;
}

int main (void) {
	startGame();

	return 0;
}