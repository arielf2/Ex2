/* All thread and resources related functions */

#include "ThreadFuncs.h"

HANDLE CreateThreadSimple(LPTHREAD_START_ROUTINE p_start_routine, LPVOID p_thread_parameters, LPDWORD p_thread_id)
{
	HANDLE thread_handle = NULL;

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

int read_from_file(READ_FILE_ARG* struct_arg) {
	char char_grade[10];
	FILE * fp = NULL;
	int file_error = 0;
	Sleep(10);
	file_error = fopen_s(&fp, struct_arg->file_name, "r");
	if (file_error != 0) {
		printf("Error in open file");
		return -1;
	}
	fgets(char_grade, LINE_IN_FILE_LENGTH, fp);
	*(struct_arg->grade) = atoi(char_grade);
	fclose(fp);

	return 0;

}

DWORD WINAPI ReadFileThread(LPVOID lpParam)
{
	READ_FILE_ARG *thread_params;
	int return_val = 0;

	/* Check if lpParam is NULL */
	if (NULL == lpParam)
	{
		return -1;
	}

	/*
	* Convert (void *) to parameters type.
	*/
	thread_params = (READ_FILE_ARG*)lpParam;

	return_val = read_from_file(thread_params);

	return return_val;
}

int CloseHandles(HANDLE thread_handles[]) {
	//close handels
	int retval;
	int func_retval = 0;
	for (int k = 0; k < NUM_OF_FILES; k++)
	{
		if (thread_handles[k] != NULL) {
			retval = CloseHandle(thread_handles[k]);
			if (0 == retval)
			{
				printf("Error when closing handles\n");
				func_retval = -1;
			}
		}
		else {
			func_retval = -1;
		}

	}
	return func_retval;
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
	return err;
}

void CloseMallocs(READ_FILE_ARG* thread_params[]) {
	//close mallocs
	for (int m = 0; m < NUM_OF_FILES; m++) {
		if (thread_params[m] != NULL) {
			free(thread_params[m]);
		}
	}
}