#include <stdio.h>

#define sscanf sscanf_s // Instead of #pragma warning (disable:4996)

#define BUF_SIZE 2

int main (void) {
	int result = 0;
	char buffer[BUF_SIZE];

	if ( fgets(buffer, BUF_SIZE, stdin) != NULL ) {
		if ( sscanf(buffer, "%1d", &result) <= 0) {
			result = 0;
		}
	}

	return result;
}