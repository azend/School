/* 
*  FILE          : CreateTheTimesTables.c
*  PROJECT       : PROG1350 - Assignment #3
*  PROGRAMMER    : Sean F. Clarke
*				   Verdi Rodrigues-Diamond
*  FIRST VERSION : Unknown
*  DESCRIPTION   :
*    The functions in this file are used to calculate
*	 the times tables from 1-9 and print it to stdout.
*/

#include <stdio.h>
#include "timetable.h"



int main()
{
	int answers[TIMES_TABLE_LENGTH][TIMES_TABLE_LENGTH];	// declare and initialize the array to hold each time table
	int loop3 = 0;
	int loop1 = 0;


	// Calculate each times table from 1-9
	for(loop1 = TIMES_TABLE_START_INDEX; loop1 < TIMES_TABLE_LENGTH; loop1++)
	{
		calculateTimesTable(answers[loop1], loop1);
	}


	// Print the full list times tables out to standard out
	for (loop1 = 1; loop1 < TIMES_TABLE_LENGTH; loop1++) {

		printf("%d Times Table\n", loop1);
		for (loop3 = 1; loop3 < 10; loop3++) {
			printf("%dx%d=%d\n", loop1, loop3, answers[loop1][loop3]);

		}
		printf("\n");

	}
	
	printf("Times Tables be Finito !!\n");
	
	return 0;
}