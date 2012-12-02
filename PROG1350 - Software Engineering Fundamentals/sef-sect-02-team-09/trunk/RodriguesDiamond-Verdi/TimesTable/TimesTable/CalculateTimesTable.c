/* 
*  FILE          : CalculateTimesTable.c
*  PROJECT       : PROG1350 - Assignment #3
*  PROGRAMMER    : Sean F. Clarke
*				   Verdi Rodrigues-Diamond
*  FIRST VERSION : Unknown
*  DESCRIPTION   :
*    The functions in this file are used to calculate
*	 and store a times table (like in elementary school)
*    and store the results in an array.
*/

#include "timetable.h"



//
// FUNCTION      : calculateTimesTable
// DESCRIPTION   :
//   This function calculates the times table
//   from 1-9 and stores it in an array
// PARAMETERS    :
//   int answers[]         : times table answers
//   int whichTimeTable    : HST tax rate
// RETURNS       :
//   void        :
//
void calculateTimesTable(int answers[], int whichTimeTable)
{

	int product;
	int loop2;
	
	// Go through every number from 1 - 9
	for(loop2 = TIMES_TABLE_START_INDEX; loop2 < TIMES_TABLE_LENGTH; loop2++)
	{

		// Calculate the product of the timest
		product = whichTimeTable * loop2;

		// so now I've got the answer for loop1 X loop2 values -- but what do I do with the answer ??
		answers[loop2] = product;
	}

}
