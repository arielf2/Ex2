#include "TestManagerFuncsAndDefs.h"

int main(int argc, char *argv[])
{
	PROCESS_INFORMATION procinfo_array[MAX_NUM_OF_STUDENTS];
	DWORD				waitcode;
	BOOL				retVal;
	HANDLE p_process_handles[MAX_NUM_OF_STUDENTS];
	STUDENT_INFO student_array[MAX_NUM_OF_STUDENTS]; //char id[10], int* grade;
	FILE *fp = NULL;
	char id[ID_LENGTH + 1] = ""; /* need extra char for \n */
	char StudentFileRelativePath[MAX_RELATIVE_PATH_LEN] = "";
	char OutputFileRelativePath[MAX_OUTPUT_FILE_LEN] = "";
	int proc_count = 0, file_error = 0, error_flag = 0, k = 0;

	strcat_s(StudentFileRelativePath, sizeof(StudentFileRelativePath), argv[1]); // input
	strcat_s(StudentFileRelativePath, sizeof(StudentFileRelativePath), GOVER_STUDENT_FILE); //input//student_ids.txt

	file_error = fopen_s(&fp, StudentFileRelativePath, "r");
	if (file_error != 0) {
		printf("Error opening %s\n", StudentFileRelativePath);
		return 1;
	}

	/* create all processes in a loop */
	while (fgets(&id, sizeof(id), fp)) {
		id[ID_LENGTH - 1] = '\0'; /* strip the line of \n*/
		strcpy_s(student_array[proc_count].id, ID_LENGTH, id);
		char command_line[COMMAND_LINE_LEN] = TEST_GRADE_PROG;

		strcat_s(command_line, sizeof(command_line), argv[1]);
		strcat_s(command_line, sizeof(command_line), GRADES_DIR);
		strcat_s(command_line, sizeof(command_line), id);

		retVal = CreateProcessSimple(command_line, &(procinfo_array[proc_count]));
		if (retVal == 0) {
			printf("Process Creation failed with error: %d", GetLastError());
			error_flag = 1;
			break;
		}
		/* Populate process handles array for WaitForMultipleObjects */
		p_process_handles[proc_count] = procinfo_array[proc_count].hProcess;
		proc_count++;
	}
	fclose(fp);
	
	/* wait for all processes to finish (if there are no errors)  */
	if (!error_flag) { // if we're here all the processes were created successfully and their number is proc_count
		waitcode = WaitForMultipleObjects(proc_count, p_process_handles, TRUE, TIMEOUT);
	}
	
	/* get ExitCodes (calculated average) from each process (student) if there are no errors */
	if (!error_flag) {
		for (int j = 0; j < proc_count; j++) {
			GetExitCodeProcess(procinfo_array[j].hProcess, &student_array[j].grade);
			if ((student_array[j].grade < 0) | (student_array[j].grade > 100)) {
				/* bad exitcode	*/
				printf("Captain, we were unable to calculate %s", student_array[j].id);
				error_flag = 1;
			}
		}
	}

	/* write output file */
	if (!error_flag) {
		printf("The grades have arrived, captain\n");
		strcat_s(OutputFileRelativePath, sizeof(OutputFileRelativePath), argv[1]);
		WriteFinalGrades(student_array, proc_count, OutputFileRelativePath, argv[1]);
	}

	/* close handles */
	for (k = 0; k < proc_count; k++) {
		CloseHandle(p_process_handles[k]);
	}

	return error_flag;
}



int WriteFinalGrades(STUDENT_INFO *StudArray, int NumOfStudents, char* OutputFile, char* GradesDir) {
	int file_error, j;
	FILE *fp = NULL;
	strcat_s(OutputFile, MAX_OUTPUT_FILE_LEN , OUTPUT_GRADE_FILE);
	file_error = fopen_s(&fp, OutputFile, "w");
	if (file_error != 0) {
		printf("Error opening final_grades.txt for writing\n");
		return 1;
	}
	for (j = 0; j < NumOfStudents; j++) {
		fprintf(fp, "%s %d\n", StudArray[j].id, StudArray[j].grade);
	}
	fclose(fp);
}

int CheckWaitCodes(int waitcode) {
	int err = 0;
	if (waitcode == WAIT_FAILED) {
		printf("WaitForMultipleObjects returned WAIT_FAILED\n");
		err = 1;
	}
	else if (waitcode == WAIT_TIMEOUT) {
		printf("WaitForMultipleObjects returned WAIT_TIMEOUT\n");
		err = 1;
	}
	else if (waitcode == WAIT_ABANDONED) {
		printf("WaitForMultipleObjects returned WAIT_ABANDONED\n");
		err = 1;
	}
	return err;
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

