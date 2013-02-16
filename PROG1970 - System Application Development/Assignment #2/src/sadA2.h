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



////////////////////////////////////////////////////
//////                                        //////
//////               CONSTANTS                //////
//////                                        //////
////////////////////////////////////////////////////

// The maximum length in bytes (and including the null-
// termination) a path can be
#define PATH_MAX 4096 // Taken from MAX_PATH in Windows.h 

// The number of bytes per line you can have when
// formatting for asm
#define ASM_LINE_BYTES_LIMIT 16

#define SRECORD_MAX_LENGTH 79 // Specified in the requirements



////////////////////////////////////////////////////
//////                                        //////
//////           TYPE DEFINITIONS             //////
//////                                        //////
////////////////////////////////////////////////////
struct Config {
	char inputFile[PATH_MAX];
	char outputFile[PATH_MAX];
	int (*filter) (struct Config* config);
};




////////////////////////////////////////////////////
//////                                        //////
//////          FUNCTION PROTOTYPES           //////
//////                                        //////
////////////////////////////////////////////////////
int asmFilter (struct Config* config);
int srecFilter (struct Config* config);
void printHelp();
void setupDefaults (struct Config* config);
int processArgs ( struct Config* config, int argc, char* argv[] );
int main (int argc, char* argv[]);
