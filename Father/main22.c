#include "main22.h"

BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr)// This part is copied from Recitation Code
{
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 }; /* <ISP> here we */
															  /* initialize a "Neutral" STARTUPINFO variable. Supplying this to */
															  /* CreateProcess() means we have no special interest in this parameter. */
															  /* This is equivalent to what we are doing by supplying NULL to most other */
															  /* parameters of CreateProcess(). */

	return CreateProcess(NULL, /*  No module name (use command line). */
		CommandLine,			/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&startinfo,				/*  Pointer to STARTUPINFO structure. */
		ProcessInfoPtr			/*  Pointer to PROCESS_INFORMATION structure. */
	);
}
int SendToSon(char *Scommand) {

	int temp_result = 0;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	char Son[LONG] = { "Son.exe " };
	strcat(Son, Scommand);
	long result;
	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;
	CHAR				command[LONG];
	memcpy(&command, &Son, sizeof(Son));
	retVal = CreateProcessSimple(command, &procinfo);

	if (retVal == 0)
	{
		printf("Process Creation Failed!\n");
		return -1;
	}


	waitcode = WaitForSingleObject(
		procinfo.hProcess,
		TIMEOUT_IN_MILLISECONDS); // Waiting 5 secs for the process to end 

	GetExitCodeProcess(procinfo.hProcess, &exitcode);// this returns the result from the son project




	CloseHandle(procinfo.hProcess); // Closing the handle to the process 
	CloseHandle(procinfo.hThread); // Closing the handle to the main thread of the process 
	return exitcode;
}

// This Function breaks the input string to mini strings as input for the son, and rebuilds the solution progress
void StatemtHandling(char* Statement, char* output, size_t sizeofStatement) {
	char Scommand[SHORT] = { '\0' },
		s_result[SHORT] = { '\0' },
		s_leftover[LONG] = { '\0' };
	int result, i_left, i_right, leftover, dist;
	char *p_leftbra = NULL, *p_rightbra = NULL, *ptr = NULL;

	
	ptr = Statement;
	for (int i = 0; i < sizeofStatement; i++) {

		if (*(ptr + i) == '(') {
			p_leftbra = ptr + i;
			i_left = i;
		}

		if (*(ptr + i) == ')') {
			p_rightbra = ptr + i;
			i_right = i;
			break;
		}
	}
	dist = p_rightbra - p_leftbra + 1; // the length of the string to be sent to Son
	memcpy(Scommand, p_leftbra + 1, dist);// building the string for Son


	
	result = SendToSon(&Scommand); // Send to Son, and get result
	_itoa(result, &s_result, 10);// cast the result to string

	
	memcpy(output, ptr, (i_left)); //copy the part before the left bracket
	strcat(output, s_result); // add the result to the new string
	leftover = sizeofStatement - i_right; // count how many chars left to copy from the previous statement

	memcpy(s_leftover, ptr + i_right+1, leftover);// copy whats left
	strcat(output, s_leftover);// finish the new statement 
	
	
	


}
//This function prints to file and to the cmd, cmd print are good for debuging.
void Printer(char* Statement, char* output, size_t sizeofStatement) { 

	char *needle = NULL;
	int left_braket = '(';
	FILE *fp;
	fp = fopen("Computation.txt", "w+");
	// check  if file opened correctly
	if (NULL != fp) {
		printf("%s\n", Statement);
		fprintf(fp, "%s\n", Statement);
		StatemtHandling(Statement, output, strlen(Statement));
		printf("%s\n", output);
		fprintf(fp,"%s\n", output);
		needle = strchr(output, left_braket); // test if any brackets left in the string, if not, we are done!
		
		while (NULL != needle) {
			memset(Statement, '\0', LONG);
			memcpy(Statement, output, LONG);
			memset(output, '\0', LONG);
			StatemtHandling(Statement, output, strlen(Statement));
			printf("%s\n", output);
			fprintf(fp,"%s\n", output);
			needle = strchr(output, left_braket);
		}
		fclose(fp);
	}
	else
	{
		printf("Error In File opening, try again.");
		exit(1);
	}
}

int main(int argc, char *argv[])
{
	char Statement[LONG] =  { '\0' } , output[LONG] = { '\0' }  ;
	char *needle = NULL;
	// Input Check
	if (argc > 2) {
		printf("Too many arguments supplied.\n");
	}
	else if (argc < 2) {
		printf("One argument expected.\n");
	}
	memcpy(Statement,argv[1],LONG);// copy to a local Variable that will be passed and modified by functions
	Printer(Statement, output, strlen(Statement));
	getchar(); // Amitay, check if this is needed, if not, please delete

	return 0;
}

