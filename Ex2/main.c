#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX_NUM_OF_STUDENTS 10
#define ID_LENGTH 10
int main()
{
	/* loop over studentsid.txt file*/
	FILE *fp = fopen("studentsid.txt", "r");
	/* check failure */
	char id[10] = "";

	PROCESS_INFORMATION procinfo_array[MAX_NUM_OF_STUDENTS];
	DWORD				waitcode;
	BOOL				retVal;

	HANDLE p_process_handles[MAX_NUM_OF_STUDENTS];
	DWORD  exitcode_array[MAX_NUM_OF_STUDENTS];
	int proc_count = 0;

	char ids_array[MAX_NUM_OF_STUDENTS][ID_LENGTH];

	/* loop for creating 10 processes, one for each student */
	while (getchar(fp) != EOF) {
		fgets(&id, ID_LENGTH, fp); /* get line (id of student) */

		strcpy_s(ids_array[proc_count], ID_LENGTH, &id);

		char command_line[27] = "";
		CreateCommandLine(&command_line, "TestGrade.exe"); /* TestGrade.txt 123456789 */

		retVal = CreateProcessSimple(command_line, &(procinfo_array[proc_count]));
		if (retVal == 0) {
			printf("Process Creation Failed!\n");
		}
		proc_count++;
	}

	for (int i = 0; i < proc_count; i++) {
		p_process_handles[i] = procinfo_array[i].hProcess;
	}

	waitcode = WaitForMultipleObjects(MAX_NUM_OF_STUDENTS, &p_process_handles, TRUE, INFINITE);
	if (waitcode == WAIT_TIMEOUT) /* Processeseseses is still alive */ {
		/* kill all processes?*/
	}

	for (int j = 0; j < proc_count; j++) {
		GetExitCodeProcess(procinfo_array[j].hProcess, &(exitcode_array[j]));/*averag*/
	}
	/* write to final file
	concat ids_array[i] and exitcode_array[i] */


	return 0;
}



BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr)
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


void CreateCommandLine()
{
}