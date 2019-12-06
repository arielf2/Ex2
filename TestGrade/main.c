/* Authors: Rotem Hecht 311143044
			Ariel Felberg 308425974
   Project: ISP Exercise 2
   Description: The TestGrade program goes over the different exercises/exam files, each in a different thread,
				then computes the average grade of the student
*/

#include "TestGradeFuncsAndDefs.h"


int main(int argc, char *argv[]) {


	char files[][MAX_FILE_NAME_SIZE] = { "ex01.txt", "ex02.txt", "ex03.txt", "ex04.txt", "ex05.txt", "ex06.txt", "ex07.txt", "ex08.txt", "ex09.txt", "ex10.txt", "midterm.txt", "moedA.txt", "moedB.txt" };
	char directory = "";
	DWORD array_thread_ids[NUM_OF_FILES];
	HANDLE thread_handles[NUM_OF_FILES];
	DWORD  exitcode_array[NUM_OF_FILES];
	float returned_grades[NUM_OF_FILES];
	READ_FILE_ARG* thread_params[NUM_OF_FILES];
	DWORD wait_code;
	int average = 0;
	int retval;
	int final_grade_return = -1;
	char id[ID_LENGTH] = "";
	DWORD process_exit_code = 0;

	GetIdFromPath(argv[1], id);
		
	for (int i = 0; i < NUM_OF_FILES; i++) {

		//create parameters for threads
		thread_params[i] = (READ_FILE_ARG *)malloc(sizeof(READ_FILE_ARG));
		if (NULL == thread_params[i])
		{
			printf("Error when allocating memory");
			process_exit_code = -1;
		}
		if (process_exit_code == 0) {
			CreatePath(argv[1], files[i], thread_params[i]->file_name);
			thread_params[i]->grade = &(returned_grades[i]);
			strcpy_s(thread_params[i]->id, ID_LENGTH, id);
		
			//create threads for each file in grades
			//initialize handle to NULL
			thread_handles[i] = NULL;
			thread_handles[i] = CreateThreadSimple(ReadFileThread, (thread_params[i]), &(array_thread_ids[i]));
			if (thread_handles[i] == NULL)//FIX//
			{
				printf("Couldn't create thread, error code %d\n", GetLastError());
				process_exit_code = -1;
			}
		}
	}

	//wait for threads to finish
	wait_code = WaitForMultipleObjects(NUM_OF_FILES, thread_handles, TRUE, INFINITE);
	process_exit_code = CheckWaitCodes(wait_code);
	if (process_exit_code == 0) {
		//Verify exit codes of all threads are fine
		LPDWORD lpExitCode;
		for (int j = 0; j < NUM_OF_FILES; j++) {
			GetExitCodeThread(thread_handles[j], &lpExitCode);
			if (lpExitCode != 0) {
				process_exit_code = -1;
			}
		}
		if (process_exit_code == 0) {
			//calc average and write it in file
			average = calc_average(returned_grades);
			final_grade_return = WriteFinalGrade(average, id, argv[1]);
			if (final_grade_return != 0) {
				printf("Error in function open file for final writing");
				process_exit_code = -1;
			}
		}
	}	

	process_exit_code = CloseHandles(thread_handles);
	CloseMallocs(thread_params);
	
	if (process_exit_code == 0) {
		process_exit_code = average;
	}
	exit(process_exit_code);
}


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

	Sleep(10);
	fopen_s(&fp, struct_arg->file_name, "r");
	if (fp == NULL) {
		printf("Error in open file");
		return -1;
	}
	fgets(char_grade, LINE_IN_FILE_LENGTH, fp);
	*(struct_arg->grade) = atoi(char_grade);
	fclose(fp);

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

int calc_average(float grades[]) {
	//add exercises value
	int max_index = -1;
	float average = 0;
	float grades_sum = 0;
	float highest_grades[HIGHEST_EXERCISES_GRADE] = { 0 };//
	float exercise_average = 0;
	int did_moed_b = 0;

	//mark if student did moed B
	if (grades[MOED_B] != 0) {
		did_moed_b = 1;
	}
	//change grades under 60 to 0 for calculation
	for (int i = 0; i < NUM_OF_FILES; i++) {
		if (grades[i] < 60) {
			grades[i] = 0;
		}
	}
	//find 8 highest grades
	for (int j = 0; j < HIGHEST_EXERCISES_GRADE; j++) {
		max_index = FindHighestGrades(grades);
		if (max_index == -1) {
			printf("Error while getting highest grade\n");
			return -1;
		}
		highest_grades[j] = grades[max_index];
		grades[max_index] = -1;

	}

	//calc average of exercises
	for (int j = 0; j < HIGHEST_EXERCISES_GRADE; j++) {
		grades_sum += highest_grades[j];
	}
	exercise_average = grades_sum / HIGHEST_EXERCISES_GRADE;

	//add exercises value
	average += 0.2*exercise_average;

	//add midterm value
	average += 0.2*grades[MIDTERM];

	//add final exam value
	if (did_moed_b == 1) {
		average += 0.6*grades[MOED_B];
	}
	else {
		average += 0.6*grades[MOED_A];
	}
	return ceil(average);
}

float FindHighestGrades(float grades[]) {
	int max = -1;
	int max_index = -1;
	for (int i = 0; i < NUM_OF_EXERCISES; i++) {
		if (grades[i] > max) {
			max = grades[i];
			max_index = i;
		}
	}
	return max_index;
}

int WriteFinalGrade(int average, char id[], char path[]) {
	char average_c[AVERAGE_SIZE];
	char final_file_name[FINAL_FILE_SIZE] = "";
	FILE *file_pointer;
	int return_value = -1;

	sprintf_s(average_c, AVERAGE_SIZE, "%d", average);
	strcat_s(final_file_name, sizeof(final_file_name), path);
	strcat_s(final_file_name, sizeof(final_file_name), "\\final_");
	strcat_s(final_file_name, sizeof(final_file_name), id);
	strcat_s(final_file_name, sizeof(final_file_name), ".txt");
	return_value = fopen_s(&file_pointer, final_file_name, "w");

	if (return_value != 0) {
		printf("Error in open file for final writing");
		return 1;
	}
	fputs(average_c, file_pointer);

	fclose(file_pointer);
	return 0;
}

void GetIdFromPath(char path[], char id[]) {
	int size = strlen(path);
	for (int i = 0; i < ID_LENGTH - 1; i++) {
		id[i] = path[size - ID_LENGTH + 1+ i];
	}
}

CreatePath(char path_from_CL[], char file_name[], char path_in_struct[]) {
	char full_file_name[PATH_TO_THREAD] = "";
	strcat_s(full_file_name, sizeof(full_file_name), path_from_CL);//////FIX
	strcat_s(full_file_name, sizeof(full_file_name), "\\");
	strcat_s(full_file_name, sizeof(full_file_name), file_name);
	strcpy_s(path_in_struct, PATH_TO_THREAD, full_file_name);
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

void CloseMallocs(READ_FILE_ARG* thread_params[]) {
	//close mallocs
	for (int m = 0; m < NUM_OF_FILES; m++) {
		if (thread_params[m] != NULL) {
			free(thread_params[m]);
		}
	}
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
	else if (waitcode == WAIT_ABANDONED) { // check if necessary
		printf("WaitForMultipleObjects returned WAIT_ABANDONED\n");
		err = 1;
	}
	return err;
}