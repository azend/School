/*
* FILE : cA5.c
* PROJECT : PROG1345 - Assignment #5
* PROGRAMMER : Verdi R-D
* FIRST VERSION : 2012-12-03
* DESCRIPTION :
* The functions in this file are used to get the
* length/size of a file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h> // :(

#include "fileUtilities_proto.h"


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
