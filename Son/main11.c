#include "main11.h"

int main(int argc, char *argv[])
{	
	// Var Declaration
	char exercise[32] = { '\0' }, temp[32] = { '\0' };
	char *p_op = NULL, *end;
	long num1, num2, result;
	// Input Check
	if (argc > 2) {
		printf("Too many arguments supplied.\n");
     }
	else if (argc <2) {
		printf("One argument expected.\n");
     }
	// handling with the string
	memcpy(&exercise, argv[1], sizeof(exercise));
	num1 = strtol(exercise, &p_op, 10);
	memcpy(&temp, p_op+1, sizeof(temp));
	num2= strtol(temp,&end,10);
	
	//Math Part
	if (p_op[0] == '*') {
		result = num1 * num2;
	}
	else if (p_op[0] == '+') {
		result = num1 + num2;
	}
	//printf("the result is %ld\n", result);// delete this later
	//getchar();
	
	return result;
}