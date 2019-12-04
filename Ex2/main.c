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
	char StudentFileRelativePath[MAX_RELATIVE_PATH_LEN] = ""; // change before submitting because running from CMD is directly in DEBUG folder
	char OutputFileRelativePath[MAX_OUTPUT_FILE_LEN] = "";
	int proc_count = 0, file_error = 0, error_flag = 0, k = 0;
	int num_of_processes_created = 0;

	//char cur_dir[100] = "";
	//GetCurrentDirectory(200, &cur_dir);
	//printf("father current directory is: %s\n", cur_dir);

	strcat_s(StudentFileRelativePath, sizeof(StudentFileRelativePath), argv[1]); // input
	strcat_s(StudentFileRelativePath, sizeof(StudentFileRelativePath), STUDENT_FILE); //input//student_ids.txt

	file_error = fopen_s(&fp, StudentFileRelativePath, "r");
	if (file_error != 0) {
		printf("Error opening %s\n", StudentFileRelativePath);
		return 1;
	}
	/*
	#define TEST_GRADE_PROG "..//Debug//TestGrade.exe "
	#define GRADES_DIR "//grades_"
	*/
	while (fgets(&id, sizeof(id), fp)) {
		id[ID_LENGTH - 1] = '\0'; /* strip the line of \n*/
		strcpy_s(student_array[proc_count].id, ID_LENGTH, id);

		char command_line[COMMAND_LINE_LEN] = TEST_GRADE_PROG;
		
		//command line should be input//grades_123456789
		strcat_s(command_line, sizeof(command_line), argv[1]);
		strcat_s(command_line, sizeof(command_line), GRADES_DIR);
		strcat_s(command_line, sizeof(command_line), id);

		//command line should be TestGrade.exe {argv[1]}//grades_{id}


		retVal = CreateProcessSimple(command_line, &(procinfo_array[proc_count]));
		if (retVal == 0) {
			printf("Process Creation failed with error: %d.\nTerminating processes 0 to %d and exiting", GetLastError(), proc_count - 1);
			//num_of_processes_created = proc_count;
			//for (k = 0; k < proc_count; k++)
			//	TerminateProcess(p_process_handles[k], 100); //change to brutal termination code
			error_flag = 1;
			break;
		}
		/* Populate process handles array for WaitForMultipleObjects */
		p_process_handles[proc_count] = procinfo_array[proc_count].hProcess;
		proc_count++;
	}

	// proc_count tells us how many processes were created successfully. so we can iterate from 0 to proc_count - 1 to terminate 
	// all the created processes s
	fclose(fp);
	if (!error_flag) { // if we're here all the processes were created successfully and their number is proc_count

		waitcode = WaitForMultipleObjects(proc_count, p_process_handles, TRUE, INFINITE);
		if (waitcode == WAIT_FAILED | waitcode == WAIT_ABANDONED_0 | waitcode == WAIT_TIMEOUT) {
			error_flag = 1;
			printf("WaitForMultipleObjects delivered bad waitcode %d with error %d\n", waitcode, GetLastError());
			//for (k = 0; k < proc_count; k++)
			//	TerminateProcess(p_process_handles[k], 100); //change to brutal termination code
		}
	}
	/* Get ExitCodes (calculated average) from each process (student) */
	/* need to fix since testgrade exitcode doesn't need to be grades */
	if (!error_flag) {
		for (int j = 0; j < proc_count; j++) {
			GetExitCodeProcess(procinfo_array[j].hProcess, &student_array[j].grade);
			if (student_array[j].grade < 0 | student_array[j].grade > 100) {
				/* bad exitcode	*/
				printf("Captain, we were unable to calculate %s", student_array[j].id);
				error_flag = 1;
			}
		}
	}
	if (!error_flag) {
		strcat_s(OutputFileRelativePath, sizeof(OutputFileRelativePath), argv[1]);
		/* need to open final_{id} and read grade from there */
		WriteFinalGrades(student_array, proc_count, OutputFileRelativePath);
	}
	/* close handles*/
	//for (k = 0; k < proc_count; k++) {
	//	TerminateProcess(p_process_handles[k], 100); //change to termination code
	//	CloseHandle(p)
	//}
	return 0;
}



int WriteFinalGrades(STUDENT_INFO *StudArray, int NumOfStudents, char* OutputFile) {
	//printf("address:%s\ndata:%s\n", &ids_array[0], ids_array[0]);
	int file_error, j;
	FILE *fp = NULL;
	strcat_s(OutputFile, MAX_OUTPUT_FILE_LEN , OUTPUT_GRADE_FILE);
	file_error = fopen_s(&fp, OutputFile, "w");
	if (file_error != 0) {
		printf("Error opening final_grades.txt for writing\n");
		return 1;
	}
	for (j = 0; j < NumOfStudents; j++) {
		printf("%s %d\n", StudArray[j].id, StudArray[j].grade); //print on console
		fprintf(fp, "%s %d\n", StudArray[j].id, StudArray[j].grade);
		
	}
	fclose(fp);
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

