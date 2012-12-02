// this funtion  does something ...
//    TODO : I need to make this a better function header comment block ...

void calculateTimesTable(int answers[], int loop1)
{

	int product;
	int loop2;
	
	for(loop2 = 1; loop2 < 10; loop2++)
	{
		product = loop1 * loop2;

		// so now I've got the answer for loop1 X loop2 values -- but what do I do with the answer ??
		answers[loop2] = product;
	}

}
