/* ===================================================================
	Programmers  : <insert your name here ...>
	Date         : Fall 2012

	Purpose      :
   =================================================================== */

#include <stdio.h>
#include "timetable.h"



int main()
{
	int answers[10][10];	// declare and initialize the array to hold each time table
	int loop3;
	int loop1;

	for(loop1=1;loop1<10;loop1++)
	{
		calculateTimesTable(answers[loop1], loop1);

		/* more code must go here - maybe to do some output ... but I am tired */
	}

	/* there - now I'm finished and the output looks good !! ... or does it ?!?!?  */

	// Print the times table out to standard out
	for (loop1 = 1; loop1 < 10; loop1++) {

		printf("%d Times Table\n", loop1);
		for (loop3 = 1; loop3 < 10; loop3++) {
			printf("%dx%d=%d\n", loop1, loop3, answers[loop1][loop3]);

		}
		printf("\n");

	}
	
	printf("Times Tables be Finito !!\n");
	
	return 0;
}