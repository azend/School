#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> // :(

#include "fileUtilities_proto.h"


// This function only works on files up to 2,147,483,647 bytes in size
int getSmallFileLength ( char* fqpn ) {
	int fileSize = -1;

	WIN32_FIND_DATA findData;
	HANDLE findHandle;

	findHandle = FindFirstFile(fqpn, &findData);

	if (findHandle != INVALID_HANDLE_VALUE) {
		fileSize = findData.nFileSizeLow;
	}
	else {
		//printf("ERROR: An error occurred while getting size of file\n");
	}

	FindClose(findHandle);

	return fileSize;

}

int readBinaryFileToBuffer (unsigned char* buffer, char* fqpn, int fileSize) {
	int result = 0;
	FILE * fp;

	if ( (fp = fopen( fqpn, "rb" )) != NULL ) {

		if ( fread(buffer, 1, fileSize, fp) == fileSize ) {
			result = 1;
		}
		else {
			printf("ERROR: Could not read file\n");
		}

		fclose(fp);

	}
	else {
		printf("ERROR: Could not open file for reading\n");
	}


	return result;
}

int writeBufferToFile (char* buffer, char* fqpn) {
	int result = 0;
	FILE * fp;

	if ( (fp = fopen( fqpn, "r" )) != NULL ) {

		fprintf(fp, "%s", buffer);

		fclose(fp);

	}
	else {
		printf("ERROR: Could not open file for reading\n");
	}

	return result;
}