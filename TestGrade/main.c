 

#include "Header.h"


int main(int argc, char *argv[]) {


	char files[][MAX_FILE_NAME_SIZE] = { "ex01.txt", "ex02.txt", "ex03.txt", "ex04.txt", "ex05.txt", "ex06.txt", "ex07.txt", "ex08.txt", "ex09.txt", "ex10.txt", "midterm.txt", "moedA.txt", "moedB.txt" };
	char directory = "";
	DWORD array_thread_ids[NUM_OF_FILES];
	HANDLE thread_handles[NUM_OF_FILES];
	DWORD  exitcode_array[NUM_OF_FILES];
	int returned_grades[NUM_OF_FILES];
	READ_FILE_ARG* thread_params[NUM_OF_FILES];
	DWORD wait_code;
	int average = 0;
	int retval;

	for (int m = 0; m < NUM_OF_FILES; m++) {
		thread_params[m] = (READ_FILE_ARG *)malloc(sizeof(READ_FILE_ARG));
		if (NULL == thread_params[m])
		{
			printf("Error when allocating memory");
			return;
		}
		strcpy_s(thread_params[m]->id, ID_LENGTH, argv[1]);
	}
	

	//strcpy_s(thread_params->id, ID_LENGTH, argv[1]);

	for (int i = 0; i < NUM_OF_FILES; i++) {
		
		thread_params[i]->grade = &(returned_grades[i]);
		//thread_params->file_name = files[i];
		strcpy_s(thread_params[i]->file_name, MAX_FILE_NAME_SIZE, files[i]);

		thread_handles[i] = CreateThreadSimple(ReadFileThread, &(thread_params[i]), &(array_thread_ids[i]));
		if (thread_handles[i] == NULL)//FIX//
		{
			printf("Couldn't create thread, error code %d\n", GetLastError());
			return;
		}
		
	}
	wait_code = WaitForMultipleObjects(NUM_OF_FILES, thread_handles, TRUE, INFINITE);
	if (wait_code == WAIT_TIMEOUT)
	{
		printf("Wait Timout \n");
		return;
	}
	else if(wait_code == WAIT_FAILED)
	{
		printf("Wait Failed \n");
		return;
	}
	else {
		/*Calculate average*/
		//add exercises value
		for (int j = 0; j < NUM_OF_EXERCISES; j++) {
			average += 0.02*returned_grades[j];
		}
		//add midterm value
		average += 0.2*returned_grades[10];//fix
		//add final exam value
		average += 0.6*returned_grades[11];//fix

		
	}

	for (int k = 0; k < NUM_OF_FILES; k++)
	{
		retval = CloseHandle(thread_handles[k]);
		if (0 == retval)
		{
			printf("Error when closing\n");
			return ;
		}
	}

	exit(average);
	//return 0;
}

HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine,
	LPVOID p_thread_parameters,
	LPDWORD p_thread_id)
{
	HANDLE thread_handle;
	printf("CreateThreadSimple\n");

	if (NULL == p_start_routine)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		exit(ERROR_CODE);
	}

	if (NULL == p_thread_id)
	{
		printf("Error when creating a thread");
		printf("Received null pointer");
		exit(ERROR_CODE);
	}

	thread_handle = CreateThread(
		NULL,                /*  default security attributes */
		0,                   /*  use default stack size */
		p_start_routine,     /*  thread function */
		p_thread_parameters, /*  argument to thread function */
		0,                   /*  use default creation flags */
		p_thread_id);        /*  returns the thread identifier */

	return thread_handle;
}


void read_from_file(READ_FILE_ARG* struct_arg) {
	printf("read_from_file\n");

	char full_file_name[500] = "..//Ex2//input//grades_";//change size
	char char_grade[10];
	strcat_s(full_file_name, sizeof(full_file_name), struct_arg->id);
	strcat_s(full_file_name, sizeof(full_file_name), "//");
	strcat_s(full_file_name, sizeof(full_file_name), struct_arg->file_name);

	FILE * fp = NULL;
	fopen_s(&fp, full_file_name, "r");
	if (fp == NULL) {
		printf("Error in open file");
		return;
	}
	fgets(char_grade, LINE_IN_FILE_LENGTH, fp);
	*(struct_arg->grade) = atoi(char_grade);
	fclose(fp);

}

DWORD WINAPI ReadFileThread(LPVOID lpParam)
{
	READ_FILE_ARG *thread_params;
	printf("ReadFileThread\n");

	/* Check if lpParam is NULL */
	if (NULL == lpParam)
	{
		return MATH_THREAD__CODE_NULL_PTR;
	}

	/*
	* Convert (void *) to parameters type.
	*/
	thread_params = (READ_FILE_ARG*)lpParam;

	read_from_file(thread_params);

	return MATH_THREAD__CODE_SUCCESS;
}
