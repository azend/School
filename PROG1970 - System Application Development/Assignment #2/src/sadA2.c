/* 
*  FILE          : sadA2.c
*  PROJECT       : PROG1970 - Assignment #2
*  PROGRAMMER    : Verdi R-D  
*  FIRST VERSION : 2013-02-15
*  DESCRIPTION   :
*    The functions in this file are used to encode
*    binary input into either assembly or Motorola
*    S-record format…
*/

#include <string.h>
#include <stdio.h>

#include "sadA2.h"



int asmFilter (struct Config* config) {
	int result = 0;

	unsigned char data[ASM_LINE_BYTES_LIMIT] = {0};
	unsigned char bytesRead = 0;
	FILE * inputFp = NULL;
	FILE * outputFp = NULL;

	int i = 0;

	// Check if the input source is from STDIN
	if ( strcmp( config->inputFile, "stdin" ) == 0 ) {
		inputFp = stdin;
	}
	// Otherwise, just use the regularly specified file
	else {
		inputFp = fopen( config->inputFile, "rb" );
	}

	if ( inputFp != NULL && ( outputFp = fopen( config->outputFile, "w" ) ) != NULL) {
		
		// Read 16 bytes (or less) and print them to the file in assembly format
		while (!feof(inputFp) && !ferror(inputFp) && !ferror(outputFp)) {
			bytesRead = fread(&data, 1, sizeof data, inputFp);
			
			fprintf(outputFp, "dc.b\t");

			for (i = 0; i < bytesRead; i++) {
				if ( i == (bytesRead - 1) ) {
					// This is the last byte that was read in
					fprintf(outputFp, "$%02x\n", data[i]);
				}
				else {
					fprintf(outputFp, "$%02x, ", data[i]);
				}
			}

		}

		if (ferror(inputFp) || ferror(outputFp)) {
			perror("The following error occurred");
			result = -2;
		}		
		else {
			fclose(outputFp);
			fclose(inputFp);
		}

	}
	else {
		printf("ERROR: An error occurred while opening streams for input.\n");
		result = -1;
	}
	
	return result;
}



int srecFilter (struct Config* config) {
	int result = 0;
	
	unsigned char bytesRead = 0;
	unsigned char data [ASM_LINE_BYTES_LIMIT];	
	unsigned char type = 1;
	unsigned char count = 0;
	unsigned int address = 0;
	unsigned int sum = 0;
	unsigned char checksum = 0;

	int i = 0;

	FILE * inputFp = NULL;
	FILE * outputFp = NULL;

	if ( strcmp( config->inputFile, "stdin" ) == 0 ) {
		inputFp = stdin;
	}
	else {
		inputFp = fopen( config->inputFile, "rb" );
	}

	if ( inputFp != NULL && ( outputFp = fopen( config->outputFile, "w" ) ) != NULL) {
		
		
		while (!feof(inputFp) && (result = ferror(inputFp) || ferror(outputFp) )) {
			
			// Read data from the source file	
			bytesRead = fread(&data, 1, sizeof data, inputFp);

			// If the address is less than 256 bytes, use an S1 record
			if ( address < (2 << 8) ) {
			type = 1;
				count = 2 + bytesRead + 1;
			}
			else if ( address < (2 << (8 * 2)) ) {
				type = 2;
				count = 3 + bytesRead + 1;
			}
			else if ( address < (2 << (8 * 3)) ) {
				type = 3;
				count = 4 + bytesRead + 1;
			}

			// Calculate the sum for using with the checksum
			sum = count + address;
			for (i = 0; i < bytesRead; i++) {
				sum += data[i];
			}

			// Checksum is the one's compliment of count, address, and data bytes
			checksum = ~(sum % 256);

			// Print out the record (I chose to do it in multiple function calls to make
			// the passed parameters at the end easier to understand)
			fprintf(outputFp, "S%01x", type);
			fprintf(outputFp, "%02x", count);
			fprintf(outputFp, "%0*x", type * 2, address);
			
			for (i = 0; i < bytesRead; i++) {
				fprintf(outputFp, "%02x", data[i]);
			}

			fprintf(outputFp, "%02x\n", checksum);

			address += ASM_LINE_BYTES_LIMIT;
		}

		if (ferror(inputFp) || ferror(outputFp)) {
			perror("The following error occurred");
			result = -2;
		}		
		else {
			fclose(outputFp);
			fclose(inputFp);
		}

	}
	else {
		printf("ERROR: An error occurred while opening streams for input.\n");
		result = -1;
	}

	return result;
}



void printHelp() {
	printf(
		"NAME\n"
			"\tencodeInput -- Encodes a given binary input into assembly or Motorola S-record format.\n"
		"\n"
		"USAGE\n"
			"\tencodeInput [-asm|-srec] [-i<inputfile>] [-o<outputfile>]\n"
		"\n"
		"OPTIONS\n"
		"-asm\t\tEncodes the file into assembly format.\n"
		"-srec\t\tEncodes the file into Motorola S-record format.\n"
		"-i<inputfile>\tInput file path. If an input file is not given, it will read from stdin.\n"
		"-o<outputfile>\tOutput file path. If an output file is not given, it will use the input file name concatenated with the performed operation name.\n"
		"\n" 
	);
}



void setupDefaults (struct Config* config) {
	// Set up defaults to initialize the struct 
	// and for the user when they omit an option
	strcpy(config->inputFile, "stdin");
	strcpy(config->outputFile, "output.asm");
	config->filter = NULL;
}




int processArgs ( struct Config* config, int argc, char* argv[] ) {
	int result = 0;
	int i = 0;
	
	if ( argc == 1 ) {
		// Only the command was run
		//printHelp();
	}
	else {
		for ( i = 1; i < argc; i++ ) {
			if ( argv[i][0] == '-' && strlen(argv[i]) > 1) {
				// This is a command line option
	
				if (argv[i][1] == 'i' && strlen(argv[i]) <= (PATH_MAX + 2)) {
					//strcpy(config->inputFile, argv[i][2]);
					if ( strlen(&argv[i][2]) > 0 && strlen(&argv[i][2]) < PATH_MAX) {
						sprintf(config->inputFile, "%s",  &argv[i][2]);
					}
					else {
						result = -3;
					} 
				}
				else if (argv[i][1] == 'o' && strlen(argv[i]) <= (PATH_MAX + 2)) {
					//strcpy(config->inputFile, argv[i][2]);
					if ( strlen(&argv[i][2]) > 0 && strlen(&argv[i][2]) < PATH_MAX) {
						sprintf(config->outputFile, "%s",  &argv[i][2]);
					}
					else {
						result = -3;
					} 
				}
				else if (argv[i][1] == 'h') {
					// Print help information
					printHelp();
					result = 1;
					break;
				}
				else if ( strncmp( &argv[i][1], "srec", 4) == 0 ) {
					if ( config->filter == NULL ) {
						config->filter = &srecFilter;
					}
					else {
						result = -2;	
					}
				}
				else if ( strncmp( &argv[i][1], "asm", 3) == 0 ) {
					if ( config->filter == NULL ) {
						config->filter = &asmFilter;
					}
					else {
						result = -2;	
					}
				}
				else {
					printf("Invalid command. Please try again.\n");
					result = -1;
					break;
				}
	
			}
		}

	}


	if ( config->filter == NULL ) {
		printf("WARNING: Encode format not specified. Defaulting to assembly.\n");
		config->filter = &asmFilter;
	}	


	return result;
}



int main (int argc, char* argv[]) {
	int result = 0;
	
	// Create a space to hold some basic config data
	struct Config config;
	
	// Initialize said data incase the user omits it when
	// they run this program
	setupDefaults( &config );

	// Process the arguments into the struct Config	
	if (processArgs ( &config, argc, argv )) {
		// If successful in processing, filter the input
		config.filter(&config);	
	}
	else {
		// Otherwise, crash :P
		printf("An unsurpassable error has occured. Please fix the issue and try again.\n");
	}
	
	return result;
}
