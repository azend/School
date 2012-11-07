#include <stdio.h>
#include <string.h>

#define MAX_AIRPORTS 128
#define MAX_FLIGHTS 128

typedef struct {
	int destinationAirportId;
	int departureTime; // In minutes since 00:00
	int flightLength; // In minutes since 00:00
} Flight;

typedef struct {
	char * name;
	Flight departures [MAX_FLIGHTS];
	int timezone;
	int visited; // 0 for no 1 for yes
} Airport;


void populateAirports (Airport airports[]) {

	char* csv = "This, is, an, example, csv";

	char* ptr = strtok(csv, ",");

	char* destinationName = (char*) *ptr;

	while (ptr != NULL) {
		
		ptr = strtok(NULL, ",");
	}

}

int main () {
	Airport airports[MAX_AIRPORTS];

	populateAirports(airports);

	return 0;
}