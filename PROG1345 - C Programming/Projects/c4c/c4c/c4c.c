#include <stdio.h>

typedef struct {
	int id;
	int departureTime; // In minutes since 00:00
	int flightLength; // In minutes since 00:00
} flight;

typedef struct {
	int id;
	char * name;
	flight * departures;
	int visited; // 0 for no 1 for yes
} city;

int main () {
	
	return 0;
}