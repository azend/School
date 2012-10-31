/* 
*  FILE          : mini2.c
*  PROJECT       : PROG1345 - Mini Assignment #2
*  PROGRAMMER    : Verdi R-D
*  FIRST VERSION : 2012-10-30
*  DESCRIPTION   :
*    The functions in this file are used to …
*/

//
// INCLUDES
//
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>



//
// FUNCTION PROTOYPES (yay!)
//
void isAlnumExample (void);
void toUpperExample (void);
void ceilExample (void);
void sqrtExample (void);
void randExample (void);
void systemExample (void);
void exitExample (void);
void memsetExample (void);
void strstrExample (void);


//
// FUNCTION      : isAlnumExample
// DESCRIPTION   :
//   This function perfoms a test on the alnum() function.
// PARAMETERS    :
//   void	: void
// RETURNS       :
//   char*	: Returns the output of the test.
//
void isAlnumExample (void) {
	
	printf(
		"int isalnum(int c);\n"
		"Checks if the passed character is alphanumeric\n"
		"Test: Is '5' alphanumeric? <%s>\n"
		"\n", 
		isalnum('5') ? "True" : "False"
	);

	return;
}



//
// FUNCTION      : toUpperExample
// DESCRIPTION   :
//   This function performs a test on the toUpper() function
// PARAMETERS    :
//   void	: void
// RETURNS       :
//   char*	: Returns the output of the test.
//
void toUpperExample (void) {
	
	printf(
		"int toupper(int c);\n"
		"Forces an alphabetic character to be uppercase\n"
		"Test: 'y' <%c>\n"
		"\n", 
		toupper('y')
	);

	return;
}



//
// FUNCTION      : ceilExample
// DESCRIPTION   :
//   This function tests the ceil() function which rounds a floating 
//   point number up to the nearst whole integer
// PARAMETERS    :
//   void	: void
// RETURNS       :
//   char*	: Returns the output of the test.
//
void ceilExample (void) {
	
	printf(
		"double ceil(double x);\n"
		"Rounds any floating point number up to the closest lying "
		"integer\n" 
		"Test: What is the ceil of 5.3? <%f>\n"
		"\n", 
		ceil(5.3)
	);

	return;
}



//
// FUNCTION      : sqrtExample
// DESCRIPTION   :
//   This function tests the C square root function
// PARAMETERS    :
//   void	: void
// RETURNS       :
//   char*	: Returns the output of the test.
//
void sqrtExample (void) {

	printf(
		"double sqrt(double x);\n"
		"Gets the square root of a floating point number\n"
		"Test: What is the square root of 9? <%f>\n"
		"\n", 
		sqrt(9)
	);

	return;
}



//
// FUNCTION      : randExample
// DESCRIPTION   :
//   This function tests both random number generation and seeding 
//   random number generation
// PARAMETERS    :
//   void	: void
// RETURNS       :
//   char*	: Returns the output of the test.
//
void randExample (void) {

	printf(
		"void srand(unsigned int seed);\n"
		"Seeds random number generation\n"
		"\n"
	);

	srand(time(NULL));

	printf(
		"int rand(void);\n"
		"Generates a random number between 0 and RAND_MAX based on the"
		" random numbers generated with srand()"
		"Test: <%d>\n"
		"\n", 
		rand()
	);

	return;
}



//
// FUNCTION      : systemExample
// DESCRIPTION   :
//   This function tests the system command
// PARAMETERS    :
//   void	: void
// RETURNS       :
//   char*	: Returns the output of the test.
//
void systemExample (void) {
	

	printf(
		"int system(const void s);\n"
		"Runs the passed string as a system command on the host machine.\n"
		"Test: Run 'dir' and print the exit code. <%d>\n"
		"\n",
		system("dir")
	);

	return;
}



//
// FUNCTION      : exitExample
// DESCRIPTION   :
//   This function gives the user a look at the exit command but does
//   not run it because it would be stupid
// PARAMETERS    :
//   void	: void
// RETURNS       :
//   char*	: Returns the output of the test.
//
void exitExample (void) {
	

	printf(
		"void exit(int status);\n"
		"Exits the program immediately with the return code 'status'\n"
		"Test: We will not test this command because it would be stupid.\n"
		"\n"
	);

	return;
}



//
// FUNCTION      : memsetExample
// DESCRIPTION   :
//   This function demonstrates the use of memset() to change memory 
//   values directly
// PARAMETERS    :
//   void	: void
// RETURNS       :
//   char*	: Returns the output of the test.
//
void memsetExample (void) {
	

	char testSubjectNumberFiveHundredandThirtySeven [] = 
		"I know about memset!";

	printf(
		"void* memset(void *p, int c, size_t n);\n"
		"Sets a memory block to the value of c.\n"
		"Test: Set the first 3 bytes of a string to \"You\" Before: <%s> ", 
		testSubjectNumberFiveHundredandThirtySeven
	);

	memset(&testSubjectNumberFiveHundredandThirtySeven, 'U', 1);

	printf(
		"After: <%s>\n"
		"\n",
		testSubjectNumberFiveHundredandThirtySeven
	);

	return;
}



//
// FUNCTION      : strstrExample
// DESCRIPTION   :
//   This function demonstrates searching a string with strstr
// PARAMETERS    :
//   void	: void
// RETURNS       :
//   char*	: Returns the output of the test.
//
void strstrExample (void) {

	printf(
		"char *strstr(const char *s1, const char *s2);\n"
		"String indexOf function for C\n"
		"Test: Get the pointer to where starts\"World\" in \"Hello"
		" World\" <%d>\n"
		"\n", 
		strstr("Hello World", "World")
	);

	return;
}




int main (void) {

	//
	// I decided to make each one of the functions print individually
	// because counting the number of bytes for snprintf() felt very
	// awkward. Also, having strcat() everywhere made my code look 
	// dirty.
	//
	isAlnumExample();
	toUpperExample();
	ceilExample();
	sqrtExample();
	randExample();
	systemExample();
	exitExample();
	memsetExample();
	strstrExample();

	return 0;
}