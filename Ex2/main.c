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
	int proc_count = 0;
	int file_error = 0;
	
	if (_chdir(argv[1])) {
		printf("Error opening Grades Directory\n");
		return 1;
	}
	//GetCurrentDirectory(200, &cur_dir);
	file_error = fopen_s(&fp, "student_ids.txt", "r");
	if (file_error != 0) {
		printf("Error opening student_ids.txt\n");
		return 1;
	}
	/* loop for creating 10 processes, one for each student */
	if (_chdir("..//..//Debug//")) {
		printf("Error changing directories\n");
	}
	while (fgets(&id, sizeof(id), fp)) {
		id[ID_LENGTH - 1] = '\0'; /* strip the line of \n*/
		strcpy_s(student_array[proc_count].id, ID_LENGTH, id);

		char command_line[COMMAND_LINE_LEN] = "TestGrade.exe ";
		if (strcat_s(command_line, 30, id)) {
			printf("Error concatenating id to program name\n");
		}
		retVal = CreateProcessSimple(command_line, &(procinfo_array[proc_count]));
		if (retVal == 0) {
			printf("Process Creation Failed with error: %d\n", GetLastError());
		}
		proc_count++;
	}
	fclose(fp);

	/* Populate process handles array for WaitForMultipleObjects */
	for (int i = 0; i < proc_count; i++) {
		p_process_handles[i] = procinfo_array[i].hProcess;
	}
	
	waitcode = WaitForMultipleObjects(proc_count, p_process_handles, TRUE, INFINITE);
	if (waitcode == WAIT_TIMEOUT) /* Processeseseses is still alive */ {
		/* kill all processes?*/
	}
	printf("waitcode = %d with error code %d\n", waitcode, GetLastError());
	/* check all wait codes */

	/* Get ExitCodes (calculated average) from each process (student) */
	for (int j = 0; j < proc_count; j++) {
		GetExitCodeProcess(procinfo_array[j].hProcess, &student_array[j].grade);
		//check exit code process
	}

	WriteFinalGrades(student_array, proc_count);
	return 0;
}



int WriteFinalGrades(STUDENT_INFO *stud_array, int num_of_students) {
	//printf("address:%s\ndata:%s\n", &ids_array[0], ids_array[0]);
	int file_error, j;
	FILE *fp = NULL;
	file_error = fopen_s(&fp, "final_grades.txt", "w");
	if (file_error != 0) {
		printf("Error opening final_grades.txt for writing\n");
		return 1;
	}
	for (j = 0; j < num_of_students; j++) {
		fprintf(fp, "%s %d\n", stud_array[j].id, stud_array[j].grade);
	}
	fclose(fp);
}
MyFunc();
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


//CreateCommandLine(&command_line, "TestGrade.exe"); /* TestGrade.txt 123456789 */
void CreateCommandLine(char* output_command, char* id)
{
	strcat_s(output_command, ID_LENGTH, id);
}
