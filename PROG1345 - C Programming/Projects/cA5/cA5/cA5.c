/*
* FILE : cA5.c
* PROJECT : PROG1345 - Assignment #5
* PROGRAMMER : Verdi R-D
* FIRST VERSION : 2012-12-03
* DESCRIPTION :
* This program takes an input binary file and outputs it
* as human readable bytes in an ascii text file.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileUtilities_proto.h"
#include "cA5_proto.h"

#define OUTPUT_FILE	"contents.txt"



//
// FUNCTION : copyBinaryFileToAsciiFile
// DESCRIPTION :
// This function copies a binary file to
// an ascii file.
// PARAMETERS :
// char* inputFqpn : fully qualified input file name
// char* outputFqpn : fully qualified output file name
// RETURNS :
// int : 0 if the command ran successfully
//       1 if the input file was less than 1 byte
//       2 if the os could not allocate enough memory to
//         read the input file
//       3 if the input or output file could not be opened
//       4 if an error occured while reading the file
//

int copyBinaryFileToAsciiFile(char* inputFqpn, char* outputFqpn) {
	int result = 0;

	int inputFileSize = 0;

	FILE *inputFile;
	FILE *outputFile;

	unsigned char * inputBuffer = {0};

	int i = 0;


	// Get the input file size
	inputFileSize = getSmallFileLength(inputFqpn);

	if (inputFileSize > 0) {

		// Allocate a memory block the size of the input file
		if ( ( inputBuffer = (unsigned char*) malloc( (inputFileSize + 1) * sizeof(unsigned char) ) ) != NULL ) {

			// Open the input and output files for use
			if ( (inputFile = fopen( inputFqpn, "rb" )) != NULL ) {
				if ( (outputFile = fopen( outputFqpn, "w" )) != NULL ) {

					// Read the input file's byte stream
					if ( fread(inputBuffer, 1, inputFileSize, inputFile) == (unsigned int) inputFileSize ) {
					
						// Print it out one at a time into the output file
						for (i = 0; i < inputFileSize; i++) {
							if ( (i + 1) % 10 == 0 ) {
								// This is a 0th digit
								fprintf(outputFile, "%03d\n", inputBuffer[i]);
							}
							else {
								fprintf(outputFile, "%03d ", inputBuffer[i]);
							}
						}

						fprintf(outputFile, "\n");

					}
					else {
						printf("ERROR: Something bad happened. An error occured while reading the input file\n");
						result = 4;
					}

					// Don't forget to close your files
					fclose(inputFile);
					fclose(outputFile);

				}
				else {
					printf("ERROR: Could not open output file for writing\n");
					result = 3;
				}
			}
			else {
				printf("ERROR: Could not open input file for reading\n");
				result = 3;
			}

			// Always remember to free your memory after a malloc()
			free(inputBuffer);
		}
		else {
			printf("ERROR: Could not allocate enough memory to read the input file\n");
			result = 2;
		}
	}
	else {
		// Either the file is too small to be read or there was an error reading the file
		result = 1;
	}


	return 0;
}

int main (int argc, char *argv[]) {

	if (argc == 2) { 
		copyBinaryFileToAsciiFile(argv[1], OUTPUT_FILE);
	}
	else {
		printf("cA5.exe <inputfile>");
	}
	

	// Get file length using stupid windows bindings
	// ...

	
	// Read and compute the file into an output buffer

	//// Allocate an input buffer room to read the entire file
	//if ( ( inputBuffer = (unsigned char*) malloc( inputFileSize * sizeof(unsigned char) ) ) != NULL && 
 //			( outputBuffer = (char*) malloc( inputFileSize * sizeof(char) ) ) != NULL ) {
	//	
	//	// Read the input file into the inputBuffer
	//	if ( readBinaryFileToBuffer(inputBuffer, "input.pdf", inputFileSize) ) {

	//		for (i = 0; i < inputFileSize; i++) {
	//			outputFileSize += strlen(tempBuffer);
	//			outputBuffer = (char*) realloc(outputBuffer, outputFileSize * sizeof(char));
	//			
	//			if ( (i + 1) % 10 == 0 ) {
	//				// This is a 0th digit
	//				sprintf(tempBuffer, "%03u\n", inputBuffer[i]);
	//				strcat(outputBuffer, tempBuffer);
	//			}
	//			else {
	//				sprintf(tempBuffer, "%03u ", inputBuffer[i]);
	//				strcat(outputBuffer, tempBuffer);
	//			}
	//		}

	//		// Write the output buffer to a file
	//		writeBufferToFile(outputBuffer, OUTPUT_FILE);

	//	}
	//}

	//free(inputBuffer);
	//free(outputBuffer);


	
	// Read the file in segments

	/*
	int fileSize = 0;
	int fileSegments = 0; // File size split by buffer size
	unsigned char fileBuffer[BUF_SIZE + 1]; // Don't forget that null bit at the end

	int x = 0;
	int y = 0;

	if ( (inputFile = fopen( "input.jpg", "rb" )) != NULL ) {
		if ( (outputFile = fopen( "output.txt", "w" )) != NULL ) {

			// Get the length of the input file
			fseek(inputFile, 0L, SEEK_END);
			fileSize = ftell(inputFile);
			fseek(inputFile, 0L, SEEK_SET);

			if (fileSize < BUF_SIZE) {
				// Read the file in one go
				if (fread(fileBuffer, 1, BUF_SIZE, inputFile) == BUF_SIZE) {
					// Read was successful
				}
				else {
					// Read could not read!
				}
				
				for (x = 0; x < fileSize; x++) {
					fprintf(outputFile, "%c", fileBuffer[x]);
				}

			}
			else {
				// Calculate file segments
				fileSegments = fileSize / BUF_SIZE;

				for (x = 0; x < fileSegments; x++) {
					fread(fileBuffer, 1, BUF_SIZE, inputFile);

					// Write buffer to output
					for (y = 0; y < BUF_SIZE; y++) {
						fprintf(outputFile, "%c", fileBuffer[y]);
					}
					
				}

				fread(fileBuffer, 1, fileSize % BUF_SIZE, inputFile);

				for (x = 0; x < fileSize % BUF_SIZE; x++) {
					fprintf(outputFile, "%c", fileBuffer[x]);
				}

			}

			fclose(inputFile);
			fclose(outputFile);

		}
		else {
			printf("ERROR: Could not open output file for writing\n");
		}
	}
	else {
		printf("ERROR: Could not open input file for reading\n");
	}
	*/

}