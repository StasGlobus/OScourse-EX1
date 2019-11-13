#include "main22.h"

BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION *ProcessInfoPtr)
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






int main()//int argc, char *argv[])
{
	int temp_result = 0;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;


	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	// Start the child process.
	/*
	if (!CreateProcess(NULL,   // No module name (use command line)
		"C:\Users\stani\OneDrive\Documents\Limudim\OS\EX1\Solution1\Debug\Son.exe 5*5", // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}
	*/
	/*
	long retVal = CreateProcess(NULL,   // No module name (use command line)
		"Son.exe 5*5", // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		;
		
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);

	// Close process and thread handles. 
	temp_result = pi.hProcess;
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	printf("%d\n", temp_result);
	*/
	
	//char test[256] = { "C:\Users\stani\OneDrive\Documents\Limudim\OS\EX1\Solution1\Debug\Son.exe 22*21" };
	long result;
	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;
	CHAR				command[] = { "Son.exe 22*21" };
	
	retVal = CreateProcessSimple(command, &procinfo);

	if (retVal == 0)
	{
		printf("Process Creation Failed!\n");
		return;
	}


	waitcode = WaitForSingleObject(
		procinfo.hProcess,
		TIMEOUT_IN_MILLISECONDS); // Waiting 5 secs for the process to end 

	GetExitCodeProcess(procinfo.hProcess, &exitcode);

	printf("The exit code for the process is %d\n", exitcode);// delete later


	CloseHandle(procinfo.hProcess); // Closing the handle to the process 
	CloseHandle(procinfo.hThread); // Closing the handle to the main thread of the process 
	//result = CreateProcess(Son test);
	
	getchar();

	




	return 0;
}