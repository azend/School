#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "unit.h"

#define TRUE	1
#define FALSE	0

#define	DEBUG	1

#define LINE_MAX_LENGTH	100
#define COLUMN_DEFAULT_WIDTH	80

void processArguments (int argc, char *argv[], char** files, int* wrapAtLastSpace, int* columnWidth) ;
int readFile (char* fileName, char** file);
char* wrapString (char* input, int wrapAtLastSpace, int columnWidth);
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

char* wrapString (char* input, int wrapAtLastSpace, int columnWidth) {
	int inputIndex = 0;
	char* output;
	int outputIndex = 0;

	if (! (output = (char*) malloc( (inputIndex + 1) * sizeof(char) ))) {
		printf("ERROR: Unable to allocate enough memory to wrap string.");
		output = "";
	}

	for ( inputIndex = 0; inputIndex < strlen(input); inputIndex++ ) {
		// Make room in the string
		if (! (output = (char*) realloc( output, (inputIndex + 1) * sizeof(char) ))) {
			printf("ERROR: Unable to allocate enough memory to wrap string.");
			output = "";
			break;
		}
		
		if (inputIndex % columnWidth == 0) {

			// Wrap line
			printf("%c\n", input[inputIndex]);
			output[outputIndex++] = input[inputIndex];
			output[outputIndex++] = '\n';

			if (wrapAtLastSpace) {

			}
			else {
				printf("%c\n", input[inputIndex]);
				output[outputIndex++] = input[inputIndex];
				output[outputIndex++] = '\n';
			}

			if ( strlen(input) > inputIndex) {

				// If the first character after a new line is a space,
				// jump it.
				if ( input[inputIndex + 1] == ' ' ) {
					inputIndex++;
				}
			}
		}
		else {
			printf("%c", input[inputIndex]);
			output[outputIndex] = input[inputIndex];
		}

		outputIndex++;
	}

	return output;
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
	int i = 1;
	

	for (i = 1; i < argc; i++) { // Start after the initial command

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

					if ( strlen (argv[i]) > 2 ) {
						// The user must have included the length in the param

						// cheater way
						// I could also make a substring
						argv[i][0] = 0;
						argv[i][1] = 0;

						*columnWidth = atoi(argv[i]);
						if ( *columnWidth == 0 ) {
							*columnWidth = COLUMN_DEFAULT_WIDTH;
						}
					}
					else {
						if ( argc > (i + 1) ) {
							*columnWidth = atoi(argv[i + 1]);
							if ( *columnWidth == 0 ) {
								*columnWidth = COLUMN_DEFAULT_WIDTH;
							}
						}
						else {
							// Display error that the command did not specify a length
						}
					}

				}

			}

			else {

				// For later use with malloc()
				//printf("%s\n", argv[i]);

				char* file;

				readFile(argv[i], &file);

				printf("%s", wrapString(file, *wrapAtLastSpace, *columnWidth));

			}

		}

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
	int columnWidth = COLUMN_DEFAULT_WIDTH;

	processArguments(argc, argv, files, &wrapAtLastSpace, &columnWidth);

	/*char* file;

	readFile("text.txt", &file);

	printf("%s", file);*/

	return 0;
}

