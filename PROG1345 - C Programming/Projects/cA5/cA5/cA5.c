
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE	1024

#define OUTPUT_FILE	output.txt

int main (int argc, char *argv[]) {
	FILE *inputFile;
	FILE *outputFile;

	char inputBuf;

	if (argc == 2) {
		printf("File: <%s>", argv[1]);

		if (inputFile = fopen(argv[1], "rb") != NULL) {
			if( outputFile = fopen(OUTPUT_FILE, "w") != NULL) {

				while( !feof(inputFile) ) {
					inputBuf = fgets(inputFile);
					fprintf(outputFile, "%c", inputBuf);
				}

				fclose(inputFile);
				fclose(outputFile);

			}
			else {
				printf(
					"Output file could not be opened"
					" for reading\n"
				);
			}
		}
		else {
			printf(
				"Input file could not be opened"
				" for reading\n"
			);
		}
	}

	else {
		printf(
			"Invalid syntax.\n"
			"cA5.exe <filein>\n"
		);
	}


	return 0;
}