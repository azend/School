#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE	1
#define FALSE	0

#define	DEBUG	1

void processArguments (int argc, char *argv[], char* files[], char* wrapAtLastSpace, int* columnWidth) ;
int readFile (char* fileName, char* file);
int getFileLength(char* fileName, int* fileLength);



int getFileLength(char* fileName, int* fileLength) {
	// Put icky os dependant stuff here
}

int readFile (char* fileName, char* file) {
	int result = 0;
	int fileLength = 0;

	FILE * fp = 0;

	if ( getFileLength(fileName, &fileLength) ) {
		char buffer[fileLength + 1];

		fp = fopen(fileName, 'r');

		if (fp != NULL) {

			fclose(fp);
		}

		else {
			printf("ERROR: Unable to open file\n");
			result = 2;
		}

	}
	else {
		printf("ERROR: Unable to get file length\n");
		result = 1;
	}

	return result;
}

void processArguments (int argc, char *argv[], char* files[], char* wrapAtLastSpace, int* columnWidth) {
	int i = 0;

	int numFiles = 0;
	
	for (i = 0; i < argc; i++) {

		if ( strlen( argv[i] )  > 1 ) {

			// Process options

			if (argv[i][0] == '-') {

				// This is a command line option
				if ( argv[i][1] == 's' /* and check length */ ) {
					// Do something
					*wrapAtLastSpace = TRUE;

				}
				else if ( argv[i][1] == 'w' /* and check length */ ) {
					// Do something with columnWidth


				}

			}

			else {
				numFiles++;
				// For later use with malloc()

			}

		}

		printf("%d - %s\n", argv[i][0], argv[i]);
	} 
}


int main (int argc, char *argv[]) {
	// …
	// Code goes here.
	// ...
	//char* files[];
	char wrapAtLastSpace = FALSE;
	int columnWidth = 40;

	//processArguments(argc, argv, &wrapAtLastSpace, &columnWidth);

	readFile("text.txt");


	return 0;
}
