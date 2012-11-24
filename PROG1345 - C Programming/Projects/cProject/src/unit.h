char * testErrorMessage;

int testChar ( char input, char expected );
int testInt ( int input, int expected );
int testLong ( long input, long expected );
int testIntArray ( int input[], int inputLength, int expected[], int expectedLength );
int testString ( char * input, char * expected );
void printTest ( char* testName, int testResult );