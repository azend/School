#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unit.h"

#define TRUE	1
#define FALSE	0

#define	DEBUG	1

#define LINE_MAX_LENGTH	100

void processArguments (int argc, char *argv[], char** files, int* wrapAtLastSpace, int* columnWidth) ;
int readFile (char* fileName, char** file);
int getFileLength(char* fileName);



int getFileLength(char* fileName) {
	// Put icky os dependant stuff here
	int result = 0;
	FILE * fp = NULL;
	
	fp = fopen(fileName, "rb");
	

	if ( fp != NULL ) {
		fseek(fp, 0L, SEEK_END);
		result = ftell(fp) + 1;
		fclose(fp);
	}
	else {
		result = -1;
	}
	
	return result;
}

int readFile (char* fileName, char** file) {
	int result = 0;
	int fileLength = 0;

	FILE * fp = NULL;

	char lineBuffer[LINE_MAX_LENGTH] = "";

	if ( (fileLength = getFileLength(fileName)) != -1 ) {
		
		*file = (char*) calloc(fileLength + 1, sizeof (char));

		if ( *file != NULL ) {
		
			fp = fopen(fileName, "r");

			if (fp != NULL) {
	
				while( fgets(lineBuffer, LINE_MAX_LENGTH, fp) != NULL ) {
					strcat(*file, lineBuffer);
				}	
					
				fclose(fp);
			}

			else {
				printf("ERROR: Unable to open file\n");
				result = 3;
			}


		}
		else {
			printf("ERROR: Could not allocate memory for reading the file\n");
			result = 2;
		}

	}
	else {
		printf("ERROR: Unable to get file length\n");
		result = 1;
	}

	return result;
}

int countArguments(int argc, char* argv[]) {
	int numArguments = 0;
	int i = 0;

	for (i = 0; i < argc; i++) {
		if ( argv[i][0] == '-' ) {
			// This is a command line switch
		}
		else {
			numArguments++;
		}
	}

	return numArguments;
}

void processArguments (int argc, char *argv[], char** files, int* wrapAtLastSpace, int* columnWidth) {
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
					printf("Using flag -s\n");

				}
				else if ( argv[i][1] == 'w' /* and check length */ ) {
					// Do something with columnWidth
					printf("Using flag -w\n");

				}

			}

			else {
				if ( ( files = (char*) malloc(
					
				numFiles++;
				// For later use with malloc()

			}

		}

		printf("%d - %s\n", argv[i][0], argv[i]);
	} 
}

int test () {
	int testsFailed = 0;

	return testsFailed;
}


int main (int argc, char *argv[]) {
	// …
	// Code goes here.
	// ...
	char** files;
	int wrapAtLastSpace = FALSE;
	int columnWidth = 40;

	processArguments(argc, argv, files, &wrapAtLastSpace, &columnWidth);

	//char* file;

	//readFile("text.txt", &file);

	//printf("%s", file);

	return 0;
}

