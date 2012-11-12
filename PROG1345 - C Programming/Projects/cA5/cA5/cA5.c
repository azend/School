
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE	1024

int main (int argc, char *argv[]) {
	if (argc == 2) {
		printf("File: <%s>", argv[1]);
	}

	else {
		printf(
			"Invalid syntax.\n"
			"cA5.exe <filein>\n"
		);
	}




	return 0;
}