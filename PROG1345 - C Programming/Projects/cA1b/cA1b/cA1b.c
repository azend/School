
/*
* FILE : cA1b.c
* PROJECT : PROG1345 - Assignment #1b
* PROGRAMMER : Verdi R-D
* FIRST VERSION : 2012-10-1
* DESCRIPTION :
* The functions in this file are used together to run a console version of the hit
* TV show Deal or no Deal.
*/

#include <stdio.h>
#include <stdlib.h>

// Enable for debug output. Lets you trace a stack trace more easily.
#define DEBUG 0

// Preferrably not handled by the precompiler but I also didn't want to hard code it.
// Also I could have passed it to each function but that is a pain in the butt
#define NUM_BRIEFCASES 26

const int kBankerRounds = 6;

/*
 * Convieniently, I haven't had to explicitly make prototypes for this game. If I were 
 * to however, they would go here
 */
void populateBriefcases (struct briefcase briefcases []);
void printClosedBriefcases (struct briefcase briefcases []);
int getNumClosedBriefcases (struct briefcase briefcases []);
int checkBriefcase (struct briefcase briefcases[], int briefcase);
float openBriefcase (struct briefcase briefcases[], int briefcase);
int getInt (char * question);
int getYesNo (char * question);
int pickInitialBriefcase (struct briefcase briefcases []);
int gameLoop (struct briefcase briefcases []);
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

//
// FUNCTION : populateBriefcases
// DESCRIPTION :
// This function populates our briefcase array with
// a random order of briefcase amounts from the show
// PARAMETERS :
// struct briefcase briefcases [] : An array, passing by reference, 
// which contains every briefcase in a struct
// RETURNS :
// void : void
//
void populateBriefcases (struct briefcase briefcases []) {
	// Terrible names for generic iterators
	int i = 0, x = 0;

	int duplicate = 0;
	int random = 0;

	float briefcaseAmounts [NUM_BRIEFCASES] = {0.01, 1.0, 5.0, 10.0, 25.0, 50.0, 75.0, 100.0, 200.0, 300.0, 400.0, 500.0, 750.0, 1000.0, 5000.0, 10000.0, 25000.0, 50000.0, 75000.0, 100000.0, 200000.0, 300000.0, 400000.0, 500000.0, 750000.0, 1000000};
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
	for (i = 0; i < NUM_BRIEFCASES; i++ ) {
		if (DEBUG) {
			printf("Suitecase %d: %d\r\n", i + 1, briefcases[i].amount);
		}
	}

	return;
}

//
// FUNCTION : printClosedBriefcases
// DESCRIPTION :
// This function prints the briefcases left in play (unopened)
// PARAMETERS :
// struct briefcase briefcases [] : An array, passing by reference, 
// which contains every briefcase in a struct
// RETURNS :
// void : void
//
void printClosedBriefcases (struct briefcase briefcases []) {
	int x;

	for (x = 0; x < NUM_BRIEFCASES; x++) {
		// If the briefcase is closed, print it's number
		if (briefcases[x].opened == 0) {
			printf("%d ", x + 1);
		}
	}
}

//
// FUNCTION : getNumClosedBriefcases
// DESCRIPTION :
// This function gets the number of briefcases left in play and returns
// it as an integer
// PARAMETERS :
// struct briefcase briefcases [] : An array, passing by reference, 
// which contains every briefcase in a struct
// RETURNS :
// int : The number of briefcases left in play
//
int getNumClosedBriefcases (struct briefcase briefcases []) {
	int x = 0;
	int numClosedBriefcases = 0;

	for (x = 0; x < NUM_BRIEFCASES; x++) {
		if (!briefcases[x].opened) {
			numClosedBriefcases++;
		}
	}
	
	return numClosedBriefcases;
}

//
// FUNCTION : checkBriefcase
// DESCRIPTION :
// This function checks whether the briefcase in the set of briefcases
// has been opened yet
// PARAMETERS :
// struct briefcase briefcases [] : An array, passing by reference, 
// which contains every briefcase in a struct
// int briefcase : The number (not id) of the briefcase to check
// RETURNS :
// int : Returns 0 if still closed and 1 if opened
//
int checkBriefcase (struct briefcase briefcases[], int briefcase) {
	int result = 0;

	if (!briefcases[briefcase - 1].opened) {
		return 1;
	}

	return result;
}

//
// FUNCTION : openBriefcase
// DESCRIPTION :
// This function marks the briefcase as opened and returns the amount 
// inside
// PARAMETERS :
// struct briefcase briefcases [] : An array, passing by reference, 
// which contains every briefcase in a struct
// int briefcase : The number (not id) of the briefcase to open
// RETURNS :
// float: The amount inside of the briefcase
//
float openBriefcase (struct briefcase briefcases[], int briefcase) {
	briefcases[briefcase - 1].opened = 1;
	if (DEBUG) printf("There is $%d in briefcase %d\r\n", briefcases[briefcase -1].amount, briefcase);

	return briefcases[briefcase -1].amount;
}

//
// FUNCTION : getInt
// DESCRIPTION :
// A utility function for going and getting an integer from the user.
// Also does validation to make sure that the user is inputing what
// you're asking.
// PARAMETERS :
// char * question : A string (or char array pointer) that contains the
// question you're asking the user (what you are asking user input for)
// RETURNS :
// int : Returns an integer from user input
//
int getInt (char * question) {
	int answer = 0;
	do {
		printf("%s: ", question);
		answer = getNum();
		printf("\r\n");
	} while (!answer);

	return answer;
}

//
// FUNCTION : getYesNo
// DESCRIPTION :
// A utility function for going and getting a yes/no style answer from 
// the user. Also does validation to make sure that the user is inputing 
// what you're asking.
// PARAMETERS :
// char * question : A string (or char array pointer) that contains the
// question you're asking the user (what you are asking user input for)
// RETURNS :
// int : Returns a boolean style integer depending on what the user answered.
// 1 is yes and 0 is no.
//
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

//
// FUNCTION : pickInitialBriefcase
// DESCRIPTION :
// This function picks the initial briefcase and holds it until the 
// end of the game
// PARAMETERS :
// struct briefcase briefcases [] : An array, passing by reference, 
// which contains every briefcase in a struct
// RETURNS :
// int : The picked briefcase id
//
int pickInitialBriefcase (struct briefcase briefcases []) {
	int selectedBriefcase = -1;

	while (selectedBriefcase == -1) {
		printf("Briefcases: ");
		printClosedBriefcases(briefcases);
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

//
// FUNCTION : gameLoop
// DESCRIPTION :
// This function runs the game's main loops such as picking briefcases and getting
// Banker offers
// PARAMETERS :
// struct briefcase briefcases [] : An array, passing by reference, 
// which contains every briefcase in a struct
// RETURNS :
// int : The condition the game is left in. 1 if the player accepted the banker's
// offer. 0 for all other cases.
//
int gameLoop (struct briefcase briefcases []) {
	int result = 0;
	int initialBriefcase = 0;
	double sum = 0;
	double roundSum = 0;
	float briefcaseAmount = 0;
	double bankerOffer = 0;
	int selectedBriefcase = 0;

	int x = 0;
	int y = 0;

	initialBriefcase = pickInitialBriefcase(briefcases);

	for (x = kBankerRounds; x > 0; x--) {
		roundSum = 0;
		if (DEBUG) printf("The variable x is: %d\n", x);
		for (y = 0; y < x; y++) {
			if (DEBUG) printf("The variable y is: %d\n", y);
			// Open some briefcases
			printf("Briefcases left: ");
			printClosedBriefcases(briefcases);
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
			if (DEBUG) printf("There are %d briefcases left in play\n", getNumClosedBriefcases(briefcases));
			if (getNumClosedBriefcases(briefcases) && x == 1) x++;
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


//
// FUNCTION : endGame
// DESCRIPTION :
// This function runs things that should be run when the game ends (ties up loose ends)
// PARAMETERS :
// int result : The game's end status
// RETURNS :
// void : void
//
void endGame (int result) {
	switch (result) {
	case 1:
		printf("You've accepted the bankers offer.");
		break;
	default:
		break;
	}
	
}

//
// FUNCTION : startGame
// DESCRIPTION :
// This function declares and initializes some values and then starts the game loop
// PARAMETERS :
// void : void
// RETURNS :
// void : void
//
void startGame (void) {
	int result;

	struct briefcase briefcases [NUM_BRIEFCASES];
	populateBriefcases(briefcases);

	result = gameLoop(briefcases);
	
	endGame(result);
}


//
// FUNCTION : getNum
// DESCRIPTION :
// This function goes and gets a number from the user
// PARAMETERS :
// void : void
// RETURNS :
// int : The number entered by the user
//

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

//
// FUNCTION : getChar
// DESCRIPTION :
// This function goes and gets a char from the user
// PARAMETERS :
// void : void
// RETURNS :
// char : The char entered by the user
//
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